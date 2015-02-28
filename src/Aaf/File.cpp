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

// C++ standard inludes
#include <cmath>

// libfalltergeist includes
#include "../Aaf/File.h"
#include "../Aaf/Glyph.h"

// Third party includes

namespace libfalltergeist
{
namespace Aaf
{

File::File(std::shared_ptr<Dat::Entry> datFileEntry): Dat::Item(datFileEntry)
{
}

File::File(std::ifstream* stream): Dat::Item(stream)
{
}

File::~File()
{
    delete [] _rgba;
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    *this >> _signature >> _maximumHeight >> _horizontalGap >> _spaceWidth >> _verticalGap;

    // glyphs info
    for (unsigned i = 0; i != 256; ++i)
    {
        uint16_t width, height;
        uint32_t offset;
        *this >> width >> height >> offset;
        if (width > _maximumWidth) _maximumWidth = width;

        _glyphs.push_back(std::shared_ptr<Glyph>(new Glyph(width, height)));
        _glyphs.back()->setDataOffset(offset);
    }
}

uint32_t* File::rgba()
{
    if (_rgba) return _rgba;
    _initialize();
    _rgba = new uint32_t[_maximumWidth * _maximumHeight * 256]();

    for (unsigned i = 0; i != 256; ++i)
    {
        uint32_t glyphY = (i/16) * _maximumHeight;
        uint32_t glyphX = (i%16) * _maximumWidth;

        // Move glyph to bottom
        glyphY += _maximumHeight - _glyphs.at(i)->height();

        setPosition(0x080C + _glyphs.at(i)->dataOffset());

        for (uint32_t y = 0; y != _glyphs.at(i)->height(); ++y)
        {
            for (uint32_t x = 0; x != _glyphs.at(i)->width(); ++x)
            {
                uint8_t byte;
                *this >> byte;

                if (byte != 0)
                {
                    uint8_t alpha = 0;
                    switch (byte)
                    {
                        case 7:
                            alpha = 255;
                            break;
                        case 6:
                            alpha = 219;
                            break;
                        case 5:
                            alpha = 169;
                            break;
                        case 4:
                            alpha = 145;
                            break;
                        case 3:
                            alpha = 116;
                            break;
                        case 2:
                            alpha = 66;
                            break;
                        case 1:
                        default:
                            alpha = 30;
                            break;
                    }

                    _rgba[(glyphY + y)*_maximumWidth*16  + glyphX + x] = 0xFFFFFF00 | alpha;
                }
            }
        }
    }
    return _rgba;
}

std::vector<std::shared_ptr<Glyph>>* File::glyphs()
{
    _initialize();
    return &_glyphs;
}

uint16_t File::horizontalGap()
{
    _initialize();
    return _horizontalGap;
}

uint16_t File::maximumHeight()
{
    _initialize();
    return _maximumHeight;
}

uint16_t File::maximumWidth()
{
    _initialize();
    return _maximumWidth;
}

uint16_t File::spaceWidth()
{
    _initialize();
    return _spaceWidth;
}

uint16_t File::verticalGap()
{
    _initialize();
    return _verticalGap;
}

}
}
