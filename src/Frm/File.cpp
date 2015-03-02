/*
 * Copyright 2012-2015 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

// C++ standard includes
#include <algorithm>

// libfalltergeist includes
#include "../Frm/Direction.h"
#include "../Frm/File.h"
#include "../Frm/Frame.h"
#include "../Pal/File.h"
#include "../Pal/Color.h"

// Third party includes

namespace libfalltergeist
{
namespace Frm
{

File::File(std::shared_ptr<Dat::Entry> datFileEntry) : Dat::Item(datFileEntry)
{
}

File::File(std::ifstream * stream) : Dat::Item(stream)
{
}

File::~File()
{
    for (auto direction : _directions)
    {
        delete direction;
    }
    delete [] _rgba;
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    *this >> _version >> _framesPerSecond >> _actionFrame >> _framesPerDirection;

    uint16_t shiftX[6];
    uint16_t shiftY[6];
    uint32_t dataOffset[6];

    for (unsigned int i = 0; i != 6; ++i) *this >> shiftX[i];
    for (unsigned int i = 0; i != 6; ++i) *this >> shiftY[i];
    for (unsigned int i = 0; i != 6; ++i)
    {
        *this >> dataOffset[i];
        if (i > 0 && dataOffset[i-1] == dataOffset[i]) continue;
        auto direction = new Direction();
        direction->setDataOffset(dataOffset[i]);
        direction->setShiftX(shiftX[i]);
        direction->setShiftY(shiftY[i]);
        _directions.push_back(direction);
    }

    // for each direction
    for (auto direction : _directions)
    {
        // jump to frames data at frames area
        Dat::Item::setPosition(direction->dataOffset() + 62);

        // read all frames
        for (unsigned i = 0; i != _framesPerDirection; ++i)
        {            
            unsigned short width, height;
            short offsetX, offsetY;

            *this >> width >> height;

            // Number of pixels for this frame
            // We don't need this, because we already have width*height
            this->skipBytes(4);

            *this >> offsetX >> offsetY;

            auto frame = new Frame(width, height);
            frame->setOffsetX(offsetX);
            frame->setOffsetY(offsetY);

            // Pixels data
            for (unsigned y = 0; y != frame->height(); ++y)
            {
                for (unsigned x = 0; x != frame->width(); ++x)
                {
                    uint8_t index;
                    *this >> index;
                    frame->setIndex(x, y, index);
                }
            }
            direction->frames()->push_back(frame);
        }
    }
}

unsigned int File::version()
{
    _initialize();
    return _version;
}

unsigned short File::framesPerSecond()
{
    _initialize();
    return _framesPerSecond;
}

unsigned short File::framesPerDirection()
{
    _initialize();
    return _framesPerDirection;
}

unsigned short File::actionFrame()
{
    _initialize();
    return _actionFrame;
}

std::vector<Direction*>* File::directions()
{
    _initialize();
    return &_directions;
}

uint16_t File::width()
{
    _initialize();
    std::vector<uint16_t> widths;
    for (auto direction : _directions)
    {
        widths.push_back(direction->width());
    }
    return *std::max_element(widths.begin(), widths.end());
}

uint16_t File::height()
{
    _initialize();
    uint16_t height = 0;

    for (auto direction : _directions)
    {
        height += direction->height();
    }
    return height;
}

unsigned int* File::rgba(std::shared_ptr<Pal::File> palFile)
{
    if (_rgba) return _rgba;
    _initialize();
    _rgba = new uint32_t[width()*height()]();

    uint16_t w = width();

    unsigned int positionY = 0;
    for (auto direction : _directions)
    {
        unsigned int positionX = 0;
        for (auto frame : *direction->frames())
        {
            for (unsigned int y = 0; y != frame->height(); ++y)
            {
                for (unsigned int x = 0; x != frame->width(); ++x)
                {
                    _rgba[((y + positionY)*w) + x + positionX] = *palFile->color(frame->index(x, y));
                }
            }
            positionX += frame->width();
        }
        positionY += direction->height();
    }
    return _rgba;
}

int File::offsetX(unsigned int direction, unsigned int frame)
{
    if (direction >= _directions.size()) direction = 0;
    return _directions.at(direction)->frames()->at(frame)->offsetX();
}

int File::offsetY(unsigned int direction, unsigned int frame)
{
    if (direction >= _directions.size()) direction = 0;
    return _directions.at(direction)->frames()->at(frame)->offsetY();
}

bool File::animatedPalette()
{
    if (_animatedMasks.empty()) animatedMasks();
    return _animatedPalette;
}

std::map<unsigned int, uint8_t*>* File::animatedMasks()
{
    if (!_animatedMasks.empty()) return &_animatedMasks;
    _initialize();

    uint16_t w = width();
    uint16_t h = height();

    unsigned int positionY = 0;
    for (auto direction : _directions)
    {
        unsigned int positionX = 0;
        for (auto frame : *direction->frames())
        {
            for (unsigned int y = 0; y != frame->height(); ++y)
            {
                for (unsigned int x = 0; x != frame->width(); ++x)
                {
                    uint8_t index = frame->index(x, y);

                    if (index >=229 && index <= 232)
                    {
                        if (!_animatedMasks[MASK_SLIME])  _animatedMasks[MASK_SLIME] = new uint8_t [w*h]();
                        _animatedMasks[MASK_SLIME][((y + positionY)*w) + x + positionX] = index;
                    }
                    else if (index >=233 && index <= 237)
                    {
                        if (!_animatedMasks[MASK_MONITOR])  _animatedMasks[MASK_MONITOR] = new uint8_t [w*h]();
                        _animatedMasks[MASK_MONITOR][((y + positionY)*w) + x + positionX] = index;

                    }
                    else if (index >=238 && index <= 242)
                    {
                        if (!_animatedMasks[MASK_FIRE_SLOW])  _animatedMasks[MASK_FIRE_SLOW] = new uint8_t [w*h]();
                        _animatedMasks[MASK_FIRE_SLOW][((y + positionY)*w) + x + positionX] = index;
                    }
                    else if (index >=243 && index <= 247)
                    {
                        if (!_animatedMasks[MASK_FIRE_FAST])  _animatedMasks[MASK_FIRE_FAST] = new uint8_t [w*h]();
                        _animatedMasks[MASK_FIRE_FAST][((y + positionY)*w) + x + positionX] = index;
                    }
                    else if (index >=248 && index <= 253)
                    {
                        if (!_animatedMasks[MASK_SHORE])  _animatedMasks[MASK_SHORE] = new uint8_t [w*h]();
                        _animatedMasks[MASK_SHORE][((y + positionY)*w) + x + positionX] = index;
                    }
                    else if (index == 254)
                    {
                        if (!_animatedMasks[MASK_REDDOT])  _animatedMasks[MASK_REDDOT] = new uint8_t [w*h]();
                        _animatedMasks[MASK_REDDOT][((y + positionY)*w) + x + positionX] = index;
                    }
                    if (index >= 229 && index <= 254)
                    {
                        _animatedPalette = true;
                    }
                }
            }
            positionX += direction->width();
        }
        positionY += direction->height();
    }
    return &_animatedMasks;
}

}
}
