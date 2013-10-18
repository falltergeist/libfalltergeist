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
#include "../src/PalColor.h"

// Third party includes

namespace libfalltergeist
{

PalColor::PalColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
    _red = red;
    _green = green;
    _blue = blue;
    _alpha = alpha;
}

PalColor::~PalColor()
{

}

void PalColor::setRed(unsigned char red)
{
    _red = red;
}

unsigned char PalColor::red()
{
    return _red;
}

void PalColor::setGreen(unsigned char green)
{
    _green = green;
}

unsigned char PalColor::green()
{
    return _green;
}

void PalColor::setBlue(unsigned char blue)
{
    _blue = blue;
}

unsigned char PalColor::blue()
{
    return _blue;
}

void PalColor::setAlpha(unsigned char alpha)
{
    _alpha = alpha;
}

unsigned char PalColor::alpha()
{
    return _alpha;
}

PalColor::operator int()
{
    return (int) (unsigned int) *this;
}

PalColor::operator unsigned int()
{
    unsigned char k = 4;
    unsigned int color = ((red() * k) << 16) | ((green() * k) << 8) | (blue() * k);
    if (color == 0) return 0;
    return (alpha() << 24) | color;
}

}
