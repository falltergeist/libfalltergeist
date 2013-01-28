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

#include "../src/LstFileType.h"
#include "../src/DatFileItem.h"
#include <iostream>

namespace libfalltergeist
{

LstFileType::LstFileType(DatFileItem * datFileItem) : _datFileItem(datFileItem)
{
    _strings = 0;
    open();
}

LstFileType::~LstFileType()
{
    delete _strings;
}

DatFileItem * LstFileType::datFileItem()
{
    return _datFileItem;
}

void LstFileType::open()
{
    // load strings from file
    _strings = new std::vector<std::string *>;

    _datFileItem->setPosition(0);

    std::string * line = new std::string();
    for(unsigned int i = 0; i != _datFileItem->size(); ++i)
    {
        unsigned char ch = _datFileItem->readUint8();
        if (ch != 0x0D)
        {
            line->push_back(ch);
        }
        else
        {
            _strings->push_back(line);
            line = new std::string();
            ++i;
            _datFileItem->skipBytes(1);
        }
    }
}

std::vector<std::string *> * LstFileType::strings()
{
    return _strings;
}

}
