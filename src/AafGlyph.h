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

#ifndef LIBFALLTERGEIST_AAFGLYPH_H
#define LIBFALLTERGEIST_AAFGLYPH_H

// C++ standard includes
#include <vector>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{

class AafGlyph
{
protected:
    unsigned short _width = 0;
    unsigned short _height = 0;
    unsigned int _dataOffset = 0;

    std::vector<unsigned char> _data;
public:
    AafGlyph(unsigned short width, unsigned short height);
    ~AafGlyph();

    std::vector<unsigned char>* data();

    AafGlyph* setWidth(unsigned short width);
    unsigned short width();

    AafGlyph* setHeight(unsigned short height);
    unsigned short height();

    unsigned int dataOffset();
    void setDataOffset(unsigned int value);
};

}
#endif // LIBFALLTERGEIST_AAFGLYPH_H
