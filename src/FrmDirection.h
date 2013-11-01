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

// C++ standard includes
#include <vector>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
class FrmFrame;

class FrmDirection
{
protected:
    signed short _shiftX;
    signed short _shiftY;
    unsigned int _dataOffset;
    std::vector<FrmFrame*> _frames;

public:
    FrmDirection();
    virtual ~FrmDirection();

    void setShiftX(signed short shiftX);
    signed short shiftX();

    void setShiftY(signed short shiftY);
    signed short shiftY();

    void setDataOffset(unsigned int offset);
    unsigned int dataOffset();

    std::vector<FrmFrame*>* frames();
};

}
#endif // LIBFALLTERGEIST_FRMDIRECTION_H
