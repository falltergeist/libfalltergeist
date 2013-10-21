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
#include <iostream>

// libfalltergeist includes
#include "../src/PalFileType.h"
#include "../src/DatFileItem.h"
#include "../src/PalColor.h"

// Third party includes

namespace libfalltergeist
{

PalFileType::PalFileType(DatFileItem * datFileItem) : _datFileItem(datFileItem)
{
    _colors = new std::vector<PalColor *>(256);
    open();
}

PalFileType::~PalFileType()
{
    delete _colors;
}

DatFileItem * PalFileType::datFileItem()
{
    return _datFileItem;
}

void PalFileType::open()
{
    DatFileItem& item = *datFileItem();

    // zero color (transparent)
    _colors->at(0) = new PalColor(0, 0, 0, 0);
    item.setPosition(3);

    for (unsigned int i = 1; i != 256; ++i)
    {
        unsigned char r, g, b;
        item >> r >> g >> b;
        _colors->at(i) = new PalColor(r, g, b);
    }
}

std::vector<PalColor *> * PalFileType::colors()
{
    return _colors;
}

PalColor * PalFileType::color(unsigned char index)
{
    return _colors->at(index);
}

}
