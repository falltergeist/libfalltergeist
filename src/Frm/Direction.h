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

#ifndef LIBFALLTERGEIST_FRM_DIRECTION_H
#define LIBFALLTERGEIST_FRM_DIRECTION_H

// C++ standard includes
#include <cstdint>
#include <vector>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
namespace Frm
{
class Frame;

class Direction      
{    
public:
    Direction();
    ~Direction();

    int16_t shiftX() const;
    void setShiftX(int16_t value);

    int16_t shiftY() const;
    void setShiftY(int16_t value);

    uint32_t dataOffset() const;
    void setDataOffset(uint32_t value);

    uint16_t width() const;
    uint16_t height() const;

    std::vector<Frame*>* frames();

protected:
    int16_t _shiftX = 0;
    int16_t _shiftY = 0;
    uint32_t _dataOffset = 0;
    std::vector<Frame*> _frames;
};

}
}
#endif // LIBFALLTERGEIST_FRM_DIRECTION_H
