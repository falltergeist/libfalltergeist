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
#include <vector>
#include <algorithm>
#include <iostream>

// libfalltergeist includes
#include "../src/RixFileType.h"

// Third party includes

namespace libfalltergeist
{

RixFileType::RixFileType(DatFileEntry* datFileEntry) : DatFileItem(datFileEntry)
{
}

RixFileType::RixFileType(std::ifstream* stream) : DatFileItem(stream)
{
}

RixFileType::~RixFileType()
{
    delete [] _rgba;
}

void RixFileType::_initialize()
{
    if (_initialized) return;
    DatFileItem::_initialize();
    DatFileItem::setPosition(0);
    
    this->readBytes(&_signature[0], 4);
    
    *this >> _width >> _height >> _unknown1;
    
    std::reverse(&reinterpret_cast<char&>(_width), &reinterpret_cast<char&>(_width) + sizeof(_width));    
    std::reverse(&reinterpret_cast<char&>(_height),&reinterpret_cast<char&>(_height) + sizeof(_height));    
    
    unsigned char k = 4;
    
    // Palette
    for (int i = 0; i != 256; ++i)
    {
        unsigned char r, g, b;
        *this >> r >> g >> b;
        unsigned int color = ((r*k) << 24) | ((g*k) << 16) | ((b*k) << 8) | 0x000000FF;  // RGBA
        _palette.push_back(color);
    }
    
    // Data
    for (int i = 0; i != _width*_height; ++i)
    {
        unsigned char ch;
        *this >> ch;
        _data.push_back(ch);
    }
}

std::vector<unsigned int>* RixFileType::palette()
{
    _initialize();
    return &_palette;
}

std::vector<unsigned char>* RixFileType::data()
{
    return &_data;
}

unsigned short RixFileType::width()
{
    _initialize();
    return _width;
}

void RixFileType::setWidth(unsigned short value)
{
    _width = value;
}

unsigned short RixFileType::height()
{
    _initialize();
    return _height;
}

void RixFileType::setHeight(unsigned short value)
{
    _height = value;
}

unsigned int* RixFileType::rgba()
{
    if (_rgba) return _rgba;
    _initialize();
    _rgba = new unsigned int[_width*_height];

    // Data
    for (int i = 0; i != _width*_height; ++i)
    {
        _rgba[i] = _palette.at(_data.at(i));
    }
    return _rgba;
}

}
