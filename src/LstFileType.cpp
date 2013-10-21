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
#include <algorithm>
#include <iostream>

// libfalltergeist includes
#include "../src/LstFileType.h"
#include "../src/DatFileEntry.h"

// Third party includes

namespace libfalltergeist
{

LstFileType::LstFileType(DatFileEntry * datFileEntry) : DatFileItem(datFileEntry)
{
    _strings = 0;
}

LstFileType::LstFileType(std::ifstream * stream) : DatFileItem(stream)
{
    _strings = 0;
}

LstFileType::~LstFileType()
{
    delete _strings;
}

void LstFileType::_initialize()
{
    if (_initialized) return;
    DatFileItem::_initialize();
    DatFileItem::setPosition(0);

    _strings = new std::vector<std::string>;

    std::string line;
    unsigned char ch;
    for(unsigned int i = 0; i != this->size(); ++i)
    {
        *this >> ch;
        if (ch != 0x0D && ch != 0x0A)
        {
            line += ch;
        }
        else
        {
            line.erase(std::find_if(line.rbegin(), line.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), line.end()); // rtrim
            _strings->push_back(line);
            line.clear();
            ++i;
            *this >> ch;
        }
    }
}

std::vector<std::string> * LstFileType::strings()
{
    _initialize();
    return _strings;
}

}
