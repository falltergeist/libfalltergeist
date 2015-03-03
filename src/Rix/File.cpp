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

// libfalltergeist includes
#include "../Rix/File.h"

// Third party includes

namespace libfalltergeist
{
namespace Rix
{

File::File(Dat::Entry* datFileEntry) : Dat::Item(datFileEntry)
{
    _initialize();
}

File::File(std::ifstream* stream) : Dat::Item(stream)
{
    _initialize();
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

    // Signature
    uint32();

    this->setEndianness(Dat::ENDIANNESS_LITTLE);
    _width = uint16();
    _height = uint16();
    this->setEndianness(Dat::ENDIANNESS_BIG);

    // Unknown 1
    uint16();

    uint32_t palette[256];

    // Palette
    for (unsigned i = 0; i != 256; ++i)
    {
        uint8_t r = uint8();
        uint8_t g = uint8();
        uint8_t b = uint8();
        palette[i] = (r << 26 | g << 18 | b << 10 | 0x000000FF);  // RGBA
    }

    _rgba = new uint32_t[_width*_height];

    // Data
    for (unsigned i = 0; i != (unsigned)_width*_height; ++i)
    {
        _rgba[i] = palette[uint8()];
    }
}

uint16_t File::width() const
{
    return _width;
}

uint16_t File::height() const
{
    return _height;
}

uint32_t* File::rgba() const
{
    return _rgba;
}

}
}
