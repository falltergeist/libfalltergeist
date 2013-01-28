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

#ifndef LIBFALLTERGEIST_FRMFRAME_H
#define LIBFALLTERGEIST_FRMFRAME_H

#include <vector>

namespace libfalltergeist
{
class PalColor;

class FrmFrame
{
protected:
    unsigned short _width;
    unsigned short _height;
    short _offsetX;
    short _offsetY;
    std::vector<unsigned char> * _colorIndexes;
public:
    FrmFrame();
    ~FrmFrame();

    void setWidth(unsigned short width);
    unsigned short width();

    void setHeight(unsigned short height);
    unsigned short height();

    void setOffsetX(short offsetX);
    short offsetX();

    void setOffsetY(short offsetY);
    short offsetY();

    std::vector<unsigned char> * colorIndexes();

};

}
#endif // LIBFALLTERGEIST_FRMFRAME_H
