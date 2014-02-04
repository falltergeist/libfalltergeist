/*
 * Copyright 2012-2014 Falltergeist Developers.
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

#ifndef LIBFALLTERGEIST_PALCOLOR_H
#define LIBFALLTERGEIST_PALCOLOR_H

// C++ standard includes

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{

class PalColor
{
protected:
    unsigned char _red;
    unsigned char _green;
    unsigned char _blue;
    unsigned char _alpha;
public:
    PalColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);
    ~PalColor();

    operator int();
    operator unsigned int();

    void setRed(unsigned char red);
    unsigned char red();

    void setGreen(unsigned char green);
    unsigned char green();

    void setBlue(unsigned char blue);
    unsigned char blue();

    void setAlpha(unsigned char alpha);
    unsigned char alpha();

};

}
#endif // LIBFALLTERGEIST_PALCOLOR_H
