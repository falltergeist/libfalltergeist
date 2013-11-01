/*
 * Copyright 2012-2013 Falltergeist Developers.
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

// libfalltergeist includes
#include "../src/FrmFileType.h"
#include "../src/FrmFrame.h"
#include "../src/FrmDirection.h"
#include "../src/DatFileEntry.h"

// Third party includes

namespace libfalltergeist
{

FrmFileType::FrmFileType(DatFileEntry * datFileEntry) : DatFileItem(datFileEntry)
{
}

FrmFileType::FrmFileType(std::ifstream * stream) : DatFileItem(stream)
{
}

FrmFileType::~FrmFileType()
{
}

void FrmFileType::_initialize()
{
    if (_initialized) return;
    DatFileItem::_initialize();
    DatFileItem::setPosition(0);

    *this >> _version >> _framesPerSecond >> _actionFrame >> _framesPerDirection;

    // X shift
    unsigned short shift;
    FrmDirection * direction;

    for (unsigned int i = 0; i != 6; ++i)
    {
        direction = new FrmDirection();
        *this >> shift;
        direction->setShiftX(shift);
        _directions.push_back(direction);
    }

    // Y shift
    for (unsigned int i = 0; i != 6; ++i)
    {
        *this >> shift;
        _directions.at(i)->setShiftY(shift);
    }

    // Data offset
    for (unsigned int i = 0; i != 6; ++i)
    {
        unsigned int offset;
        *this >> offset;
        _directions.at(i)->setDataOffset(offset);
    }

    // for each direction
    for (unsigned int i = 0; i!= 6; ++i)
    {
        // jump to frames data at frames area
        DatFileItem::setPosition(_directions.at(i)->dataOffset() + 62);

        // read all frames
        for (unsigned int j = 0; j != _framesPerDirection; ++j)
        {
            FrmFrame * frame = new FrmFrame();

            unsigned short width, height;

            *this >> width >> height;

            // Frame width
            frame->setWidth(width);

            // Frame height
            frame->setHeight(height);

            //Number of pixels for this frame
            unsigned int dataSize;
            *this >> dataSize;

            short offsetX, offsetY;
            *this >> offsetX >> offsetY;

            // X offset
            frame->setOffsetX(offsetX);

            // Y offset
            frame->setOffsetY(offsetY);


            for (unsigned int n = 0; n != dataSize; ++n)
            {
                // Pixel color index
                unsigned char color;
                *this >> color;
                frame->colorIndexes()->push_back(color);
            }
            // Appending frame to direction
            _directions.at(i)->frames()->push_back(frame);
        }
    }
}

unsigned int FrmFileType::version()
{
    _initialize();
    return _version;
}

void FrmFileType::setVersion(unsigned int version)
{
    _version = version;
}

unsigned short FrmFileType::framesPerSecond()
{
    _initialize();
    return _framesPerSecond;
}

void FrmFileType::setFramesPerSecond(unsigned short fps)
{
    _framesPerSecond = fps;
}

unsigned short FrmFileType::framesPerDirection()
{
    _initialize();
    return _framesPerDirection;
}

void FrmFileType::setFramesPerDirection(unsigned short fpd)
{
    _framesPerDirection = fpd;
}

unsigned short FrmFileType::actionFrame()
{
    _initialize();
    return _actionFrame;
}

void FrmFileType::setActionFrame(unsigned short number)
{
    _actionFrame = number;
}

std::vector<FrmDirection*>* FrmFileType::directions()
{
    _initialize();
    return &_directions;
}

}
