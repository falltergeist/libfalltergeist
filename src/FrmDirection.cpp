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

#include "../src/FrmDirection.h"
#include "../src/FrmFrame.h"

namespace libfalltergeist
{

FrmDirection::FrmDirection()
{
    _frames = 0;
}

FrmDirection::~FrmDirection()
{
    delete _frames;
}

/**
 * Alias to FrmDirection::getShiftX
 * @brief FrmDirection::shiftX
 * @return
 */
short FrmDirection::shiftX()
{
    return getShiftX();
}

short FrmDirection::getShiftX()
{
    return _shiftX;
}

void FrmDirection::setShiftX(short shiftX)
{
    _shiftX = shiftX;
}

/**
 * Alias to FrmDirection getShiftY
 * @brief FrmDirection::shiftY
 * @return
 */
short FrmDirection::shiftY()
{
    return getShiftY();
}

short FrmDirection::getShiftY()
{
    return _shiftY;
}

void FrmDirection::setShiftY(short shiftY)
{
    _shiftY = shiftY;
}

/**
 * Alias to FrmDirection::getDataOffset
 * @brief FrmDirection::dataOffset
 * @return
 */
unsigned int FrmDirection::dataOffset()
{
    return getDataOffset();
}

unsigned int FrmDirection::getDataOffset()
{
    return _dataOffset;
}

void FrmDirection::setDataOffset(unsigned int offset)
{
    _dataOffset = offset;
}

/**
 * Alias to FrmDirection::getFrames
 * @brief FrmDirection::frames
 * @return
 */
std::vector<FrmFrame *> * FrmDirection::frames()
{
    return getFrames();
}

std::vector<FrmFrame *> * FrmDirection::getFrames()
{
    if (_frames != 0) return _frames;
    _frames = new std::vector<FrmFrame *>;
    return _frames;
}

}
