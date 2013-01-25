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

void LstFileType::open()
{
    // load strings from file
    _strings = new std::vector<std::string *>;

    _datFileItem->setPosition(0);

    bool end = false;

    for(unsigned int i = 0; i != _datFileItem->size(); ++i)
    {
        std::string * line = new std::string();
        unsigned char ch;
        while (ch = _datFileItem->readUint8() && ch != 0x0D && i < _datFileItem->size())
        {
            if (ch == 0x20) end = true;
            if (!end) line->push_back(ch);
            i++;
        }
        end = false;
        // skips \r\n
        i++; i++;
        _strings->push_back(line);
    }
}

std::vector<std::string *> * LstFileType::getStrings()
{
    return _strings;
}

}
