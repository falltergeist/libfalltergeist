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

// C++ standard includes

// libfalltergeist includes
#include "../src/FrmDirection.h"
#include "../src/FrmFrame.h"

// Third party includes

namespace libfalltergeist
{

FrmDirection::FrmDirection()
{
}

FrmDirection::~FrmDirection()
{
}

signed short FrmDirection::shiftX()
{
    return _shiftX;
}

void FrmDirection::setShiftX(signed short shiftX)
{
    _shiftX = shiftX;
}

signed short FrmDirection::shiftY()
{
    return _shiftY;
}

void FrmDirection::setShiftY(signed short shiftY)
{
    _shiftY = shiftY;
}

unsigned int FrmDirection::dataOffset()
{
    return _dataOffset;
}

void FrmDirection::setDataOffset(unsigned int offset)
{
    _dataOffset = offset;
}

std::vector<FrmFrame*>* FrmDirection::frames()
{
    return &_frames;
}

}
