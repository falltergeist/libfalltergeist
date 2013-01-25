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

#include "../src/AafGlyph.h"

namespace libfalltergeist
{

AafGlyph::AafGlyph()
{
    _height = 0;
    _width = 0;
    _data = new std::vector<unsigned char>;
}

AafGlyph::~AafGlyph()
{
    delete _data;
}

unsigned short AafGlyph::getHeight()
{
    return _height;
}

void AafGlyph::setHeight(unsigned short height)
{
    _height = height;
}

unsigned short AafGlyph::getWidth()
{
    return _width;
}

void AafGlyph::setWidth(unsigned short width)
{
    _width = width;
}

std::vector<unsigned char> * AafGlyph::getData()
{
    return _data;
}


}
