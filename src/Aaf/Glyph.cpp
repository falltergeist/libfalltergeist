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
#include "../Aaf/Glyph.h"

// Third party includes

namespace libfalltergeist
{
namespace Aaf
{

Glyph::Glyph(uint16_t width, uint16_t height) : _width(width), _height(height)
{
}

Glyph::~Glyph()
{
}

uint16_t Glyph::height()
{
    return _height;
}

Glyph* Glyph::setHeight(uint16_t height)
{
    _height = height;
    return this;
}

uint16_t Glyph::width()
{
    return _width;
}

Glyph* Glyph::setWidth(uint16_t width)
{
    _width = width;
    return this;
}

std::vector<unsigned char>* Glyph::data()
{
    return &_data;
}

uint32_t Glyph::dataOffset()
{
    return _dataOffset;
}

void Glyph::setDataOffset(uint32_t value)
{
    _dataOffset = value;
}

}
}
