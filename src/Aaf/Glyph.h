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

#ifndef LIBFALLTERGEIST_GLYPH_H
#define LIBFALLTERGEIST_GLYPH_H

// C++ standard includes
#include <cstdint>
#include <vector>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
namespace Aaf
{

class Glyph
{

public:
    Glyph(uint16_t width, uint16_t height);
    ~Glyph();

    std::vector<unsigned char>* data();

    uint16_t width() const;
    void setWidth(uint16_t width);

    uint16_t height() const;
    void setHeight(uint16_t height);

    uint32_t dataOffset() const;
    void setDataOffset(uint32_t value);

protected:
    uint16_t _width = 0;
    uint16_t _height = 0;
    uint32_t _dataOffset = 0;

    std::vector<unsigned char> _data;

};

}
}
#endif // LIBFALLTERGEIST_GLYPH_H
