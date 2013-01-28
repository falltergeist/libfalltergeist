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

#ifndef LIBFALLTERGEIST_PALFILETYPE_H
#define LIBFALLTERGEIST_PALFILETYPE_H

#include <vector>

namespace libfalltergeist
{
class DatFileItem;
class PalColor;

class PalFileType
{
protected:
    DatFileItem * _datFileItem;
    std::vector<PalColor *> * _colors;

public:
    PalFileType(DatFileItem * datFileItem);
    ~PalFileType();

    DatFileItem * datFileItem();
    DatFileItem * getDatFileItem();

    void open();    

    std::vector<PalColor *> * colors();
    std::vector<PalColor *> * getColors();

    PalColor * color(unsigned char index);
    PalColor * getColor(unsigned char index);

};

}
#endif // LIBFALLTERGEIST_PALFILETYPE_H
