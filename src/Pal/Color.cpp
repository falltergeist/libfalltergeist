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
#include "../Pal/Color.h"

// Third party includes

namespace libfalltergeist
{
namespace Pal
{

Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
    _red = red;
    _green = green;
    _blue = blue;
    _alpha = alpha;
}

Color::~Color()
{

}

void Color::setRed(unsigned char red)
{
    _red = red;
}

unsigned char Color::red()
{
    return _red;
}

void Color::setGreen(unsigned char green)
{
    _green = green;
}

unsigned char Color::green()
{
    return _green;
}

void Color::setBlue(unsigned char blue)
{
    _blue = blue;
}

unsigned char Color::blue()
{
    return _blue;
}

void Color::setAlpha(unsigned char alpha)
{
    _alpha = alpha;
}

unsigned char Color::alpha()
{
    return _alpha;
}

Color::operator int()
{
    return (int) (unsigned int) *this;
}

Color::operator unsigned int()
{
    unsigned char k = 4;
    return ((red() * k) << 24) | ((green() * k) << 16) | ((blue() * k) << 8) | alpha();
}

}
}
