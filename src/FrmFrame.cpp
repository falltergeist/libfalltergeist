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

#include "../src/FrmFrame.h"
#include "../src/PalColor.h"

namespace libfalltergeist
{

FrmFrame::FrmFrame()
{
    _colorIndexes = 0;
}

FrmFrame::~FrmFrame()
{
    delete _colorIndexes;
}

/**
 * Alias to FrmFrame::getWidth
 * @brief FrmFrame::width
 * @return
 */
unsigned short FrmFrame::width()
{
    return getWidth();
}

unsigned short FrmFrame::getWidth()
{
    return _width;
}

void FrmFrame::setWidth(unsigned short width)
{
    _width = width;
}

/**
 * Alias to FrmFrame::getHeight
 * @brief FrmFrame::height
 * @return
 */
unsigned short FrmFrame::height()
{
    return getHeight();
}

unsigned short FrmFrame::getHeight()
{
    return _height;
}

void FrmFrame::setHeight(unsigned short height)
{
    _height = height;
}

/**
 * Alias to FrmFrame::getOffsetX
 * @brief FrmFrame::offsetX
 * @return
 */
short FrmFrame::offsetX()
{
    return getOffsetX();
}

short FrmFrame::getOffsetX()
{
    return _offsetX;
}

void FrmFrame::setOffsetX(short offsetX)
{
    _offsetX = offsetX;
}

/**
 * Alias to FrmFrame::getOffsetY
 * @brief FrmFrame::offsetY
 * @return
 */
short FrmFrame::offsetY()
{
    return getOffsetY();
}

short FrmFrame::getOffsetY()
{
    return _offsetY;
}

void FrmFrame::setOffsetY(short offsetY)
{
    _offsetY = offsetY;
}

/**
 * Alias to FrmFrame::getColorIndexes
 * @brief FrmFrame::colorIndexes
 * @return
 */
std::vector<unsigned char> * FrmFrame::colorIndexes()
{
    return getColorIndexes();
}

std::vector<unsigned char> * FrmFrame::getColorIndexes()
{
    if (_colorIndexes != 0) return _colorIndexes;
    _colorIndexes = new std::vector<unsigned char>;
    return _colorIndexes;
}


}
