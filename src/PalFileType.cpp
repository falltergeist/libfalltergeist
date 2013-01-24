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

#include "../src/PalFileType.h"
#include "../src/DatFileItem.h"
#include "../src/PalColor.h"

namespace libfalltergeist
{

PalFileType::PalFileType(DatFileItem * datFileItem) : _datFileItem(datFileItem)
{
    _colors = 0;
    open();
}

PalFileType::~PalFileType()
{
    delete _colors;
}

void PalFileType::open()
{
    _datFileItem->setPosition(0);
    _colors = new std::vector<PalColor *>;

    // zero color (transparent)
    _colors->push_back(new PalColor(0,0,0,0));
    _datFileItem->skipBytes(3);

    for (unsigned int i = 1; i != 256; ++i)
    {
        unsigned char r = _datFileItem->readUint8();
        unsigned char g = _datFileItem->readUint8();
        unsigned char b = _datFileItem->readUint8();        

        _colors->push_back(new PalColor(r,g,b));
    }
}

std::vector<PalColor *> * PalFileType::getColors()
{
    return _colors;
}

PalColor * PalFileType::getColor(unsigned char index)
{
    return _colors->at(index);
}

}
