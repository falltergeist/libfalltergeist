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
#include <algorithm>

// libfalltergeist includes
#include "../Frm/Direction.h"
#include "../Frm/Frame.h"

// Third party includes

namespace libfalltergeist
{
namespace Frm
{

Direction::Direction()
{
}

Direction::~Direction()
{
    for (auto frame : _frames)
    {
        delete frame;
    }
}

int16_t Direction::shiftX() const
{
    return _shiftX;
}

void Direction::setShiftX(int16_t value)
{
    _shiftX = value;
}

int16_t Direction::shiftY() const
{
    return _shiftY;
}

void Direction::setShiftY(int16_t value)
{
    _shiftY = value;
}

uint32_t Direction::dataOffset() const
{
    return _dataOffset;
}

uint16_t Direction::width() const
{
    std::vector<uint16_t> widths;
    for (auto frame : _frames)
    {
        widths.push_back(frame->width());
    }
    return (*std::max_element(widths.begin(), widths.end())) * _frames.size();
}

uint16_t Direction::height() const
{
    std::vector<uint16_t> heights;
    for (auto frame : _frames)
    {
        heights.push_back(frame->height());
    }
    return *std::max_element(heights.begin(), heights.end());
}

void Direction::setDataOffset(uint32_t value)
{
    _dataOffset = value;
}

std::vector<Frame*>* Direction::frames()
{
    return &_frames;
}

}
}
