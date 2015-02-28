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

File::File(std::shared_ptr<Dat::Entry> datFileEntry) : Dat::Item(datFileEntry)
{
}

File::File(std::ifstream* stream) : Dat::Item(stream)
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

    // Signature
    this->skipBytes(4);

    this->setEndianness(Dat::ENDIANNESS_LITTLE);
    *this >> _width >> _height;
    this->setEndianness(Dat::ENDIANNESS_BIG);

    // Unknown 1
    this->skipBytes(2);

    unsigned int palette[256];

    // Palette
    for (int i = 0; i != 256; ++i)
    {
        unsigned char r, g, b;
        *this >> r >> g >> b;
        unsigned int color = r << 26 | g << 18 | b << 10 | 0x000000FF;  // RGBA
        palette[i] = color;
    }

    _rgba = new unsigned int[_width*_height];
    // Data
    for (int i = 0; i != _width*_height; ++i)
    {
        unsigned char ch;
        *this >> ch;
        _rgba[i] = palette[ch];
    }
}

unsigned short File::width()
{
    _initialize();
    return _width;
}

unsigned short File::height()
{
    _initialize();
    return _height;
}

unsigned int* File::rgba()
{
    _initialize();
    return _rgba;
}

}
}
