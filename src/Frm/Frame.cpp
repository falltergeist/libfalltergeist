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
#include "../Frm/Frame.h"

// Third party includes

namespace libfalltergeist
{
namespace Frm
{

Frame::Frame(uint16_t width, uint16_t height)
{
    _width = width;
    _height = height;

    for (unsigned i = 0; i != (unsigned)_width*_height; ++i)
    {
        _indexes.push_back(0);
    }
}

Frame::Frame(const Frame& other)
{
    _width = other._width;
    _height = other._height;
    _offsetX = other._offsetX;
    _offsetY = other._offsetY;
    _indexes = other._indexes;
}

Frame::~Frame()
{
}

uint16_t Frame::width() const
{
    return _width;
}

uint16_t Frame::height() const
{
    return _height;
}

int16_t Frame::offsetX() const
{
    return _offsetX;
}

void Frame::setOffsetX(int16_t value)
{
    _offsetX = value;
}

int16_t Frame::offsetY() const
{
    return _offsetY;
}

void Frame::setOffsetY(int16_t value)
{
    _offsetY = value;
}

const std::vector<uint8_t>* Frame::indexes() const
{
    return &_indexes;
}

uint8_t Frame::index(uint16_t x, uint16_t y) const
{
    if (x >= _width || y >= _height) return 0;

    return _indexes.at(_width*y + x);
}

void Frame::setIndex(uint16_t x, uint16_t y, uint8_t index)
{
    if (x >= _width || y >= _height) return;

    _indexes.at(_width*y + x) = index;
}

}
}
