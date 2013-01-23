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

#include "../src/PalColor.h"

namespace libfalltergeist
{

PalColor::PalColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a)
{
}

PalColor::operator int()
{
    unsigned char k = 1;
    int color = ((r * k) << 16) | ((g * k) << 8) | (b * k);
    if (color == 0) return 0;
    return 0xFF000000 | color;
}

PalColor::operator unsigned int()
{
    unsigned char k = 1;
    unsigned int color = ((r * k) << 16) | ((g * k) << 8) | (b * k);
    if (color == 0) return 0;
    return 0xFF000000 | color;
}

}
