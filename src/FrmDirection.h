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

#ifndef LIBFALLTERGEIST_FRMDIRECTION_H
#define LIBFALLTERGEIST_FRMDIRECTION_H

#include <vector>

namespace libfalltergeist
{
class FrmFrame;

class FrmDirection
{
protected:
    short _shiftX;
    short _shiftY;
    unsigned int _dataOffset;
    std::vector<FrmFrame *> * _frames;

public:
    FrmDirection();
    ~FrmDirection();

    void setShiftX(short shiftX);
    short shiftX();

    void setShiftY(short shiftY);
    short shiftY();

    void setDataOffset(unsigned int offset);
    unsigned int dataOffset();

    std::vector<FrmFrame *> * frames();
};

}
#endif // LIBFALLTERGEIST_FRMDIRECTION_H
