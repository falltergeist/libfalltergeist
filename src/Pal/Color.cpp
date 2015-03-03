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

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    _red = red;
    _green = green;
    _blue = blue;
    _alpha = alpha;
}

Color::~Color()
{
}

void Color::setRed(uint8_t red)
{
    _red = red;
}

uint8_t Color::red() const
{
    return _red;
}

void Color::setGreen(uint8_t green)
{
    _green = green;
}

uint8_t Color::green() const
{
    return _green;
}

void Color::setBlue(uint8_t blue)
{
    _blue = blue;
}

uint8_t Color::blue() const
{
    return _blue;
}

void Color::setAlpha(uint8_t alpha)
{
    _alpha = alpha;
}

uint8_t Color::alpha() const
{
    return _alpha;
}

Color::operator int() const
{
    return (int) (unsigned int) *this;
}

Color::operator unsigned int() const
{
    uint8_t k = 4;
    return ((red() * k) << 24) | ((green() * k) << 16) | ((blue() * k) << 8) | alpha();
}

}
}
