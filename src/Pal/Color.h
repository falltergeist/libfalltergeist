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

#ifndef LIBFALLTERGEIST_PAL_COLOR_H
#define LIBFALLTERGEIST_PAL_COLOR_H

// C++ standard includes
#include <cstdint>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
namespace Pal
{

class Color
{

public:
    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
    ~Color();

    operator int() const;
    operator unsigned int() const;

    void setRed(uint8_t red);
    uint8_t red() const;

    void setGreen(uint8_t green);
    uint8_t green() const;

    void setBlue(uint8_t blue);
    uint8_t blue() const;

    void setAlpha(uint8_t alpha);
    uint8_t alpha() const;

protected:
    uint8_t _red;
    uint8_t _green;
    uint8_t _blue;
    uint8_t _alpha;


};

}
}
#endif // LIBFALLTERGEIST_PAL_COLOR_H
