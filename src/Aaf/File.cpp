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

File::File(Dat::Entry* datFileEntry): Dat::Item(datFileEntry)
{
    _initialize();
}

File::File(std::ifstream* stream): Dat::Item(stream)
{
    _initialize();
}

File::~File()
{
    for (auto glyph : _glyphs)
    {
        delete glyph;
    }
    delete [] _rgba;
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    _signature     = uint32(); // should be "AAFF"
    _maximumHeight = uint16();
    _horizontalGap = uint16();
    _spaceWidth    = uint16();
    _verticalGap   = uint16();

    // Glyphs info
    for (unsigned i = 0; i != 256; ++i)
    {
        uint16_t width  = uint16();
        uint16_t height = uint16();
        uint32_t offset = uint32();

        if (width > _maximumWidth)
        {
            _maximumWidth = width;
        }

        _glyphs.push_back(new Glyph(width, height));
        _glyphs.back()->setDataOffset(offset);
    }
}

uint32_t* File::rgba()
{
    if (_rgba) return _rgba;
    _rgba = new uint32_t[_maximumWidth * _maximumHeight * 256]();

    for (unsigned i = 0; i != 256; ++i)
    {
        uint32_t glyphY = (i/16) * _maximumHeight;
        uint32_t glyphX = (i%16) * _maximumWidth;

        // Move glyph to bottom
        glyphY += _maximumHeight - _glyphs.at(i)->height();

        setPosition(0x080C + _glyphs.at(i)->dataOffset());

        for (uint16_t y = 0; y != _glyphs.at(i)->height(); ++y)
        {
            for (uint16_t x = 0; x != _glyphs.at(i)->width(); ++x)
            {
                uint8_t byte = uint8();
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

std::vector<Glyph*>* File::glyphs()
{
    return &_glyphs;
}

uint16_t File::horizontalGap() const
{
    return _horizontalGap;
}

uint16_t File::maximumHeight() const
{
    return _maximumHeight;
}

uint16_t File::maximumWidth() const
{
    return _maximumWidth;
}

uint16_t File::spaceWidth() const
{
    return _spaceWidth;
}

uint16_t File::verticalGap() const
{
    return _verticalGap;
}

}
}
