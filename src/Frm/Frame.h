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

#ifndef LIBFALLTERGEIST_FMR_FRAME_H
#define LIBFALLTERGEIST_FMR_FRAME_H

// C++ standard includes
#include <cstdint>
#include <vector>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
namespace Frm
{

class Frame
{

public:
    Frame(uint16_t width, uint16_t height);
    Frame(const Frame& other);
    ~Frame();

    uint16_t width() const;
    uint16_t height() const;

    int16_t offsetX() const;
    void setOffsetX(int16_t value);

    int16_t offsetY() const;
    void setOffsetY(int16_t value);

    const std::vector<uint8_t>* indexes() const;

    uint8_t index(uint16_t x, uint16_t y) const;
    void setIndex(uint16_t x, uint16_t y, uint8_t index);

protected:
    uint16_t _width = 0;
    uint16_t _height = 0;
    int16_t _offsetX = 0;
    int16_t _offsetY = 0;
    std::vector<uint8_t> _indexes;

};

}
}
#endif // LIBFALLTERGEIST_FMR_FRAME_H
