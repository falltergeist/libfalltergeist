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
#include "../src/IntFileType.h"
#include "../src/Exception.h"

// Third party includes

namespace libfalltergeist
{

IntFileType::IntFileType(DatFileEntry* datFileEntry) : DatFileItem(datFileEntry)
{
}

IntFileType::IntFileType(std::ifstream* stream) : DatFileItem(stream)
{
}

IntFileType::~IntFileType()
{
}

void IntFileType::_initialize()
{
    if (_initialized) return;
    DatFileItem::_initialize();
    DatFileItem::setPosition(0);


    // HEADER
    setPosition(12);
    *this >> _entryPoint;
    std::cout << "Entry point: " << std::hex << _entryPoint << std::endl;

    // FUNCTIONS TABLE
    setPosition(42);
    unsigned int functionsTableSize;
    *this >> functionsTableSize;

    std::cout << "Functions table size: " << std::dec << functionsTableSize << std::endl;

    std::map<unsigned int, unsigned int> functions;

    for (unsigned int i = 0; i != functionsTableSize; ++i)
    {

        unsigned int nameOffset;
        unsigned int entryPoint;
        *this >> nameOffset;
        skipBytes(12);
        *this >> entryPoint;
        skipBytes(4);
        functions.insert(std::make_pair(nameOffset, entryPoint));
        //std::cout << "Function: nameOffset = " << std::hex << nameOffset << " : entryPoint = " << entryPoint << std::endl;
    }

    // IDENTIFICATORS TABLE
    unsigned int identificatorsTableSize;
    *this >> identificatorsTableSize;
    std::cout << "Identificators table size: " << std::dec << identificatorsTableSize << std::endl;

    std::map<unsigned int, std::string> identificators;
    unsigned int j = 0;
    while (j < identificatorsTableSize)
    {
        unsigned short length;
        std::string name;
        *this >> length;
        j += 2;
        unsigned int nameOffset = j + 4;
        for (unsigned int i = 0; i != length; ++i, ++j)
        {
            unsigned char ch;
            *this >> ch;
            if (ch != 0) name.push_back(ch);
        }

        identificators.insert(std::make_pair(nameOffset, name));
        //std::cout << "Inentificator: nameOffset = " << std::hex << nameOffset << " : name = " << name << std::endl;
    }

    for (auto it = functions.begin(); it != functions.end(); ++it)
    {
        _functionsName.push_back(identificators.at(it->first));
        _functions.insert(std::make_pair(identificators.at(it->first), it->second));
    }

    unsigned int signature; // must be 0xFFFFFFFF
    *this >> signature;
    std::cout << "Signature: " << std::hex << signature << std::endl;

    // STRINGS TABLE

    unsigned int stringsTableSize;
    *this >> stringsTableSize;

    if (stringsTableSize != 0xFFFFFFFF)
    {
        std::cout << "Strings table size: " << std::dec << stringsTableSize << std::endl;
        skipBytes(stringsTableSize);
        *this >> signature;
        std::cout << "Signature: " << std::hex << signature << std::endl;
    }
    else
    {
        std::cout << "Strings table size: 0xFFFFFFFF" << std::endl;
    }
}

void IntFileType::test()
{
    _initialize();
}

unsigned int IntFileType::function(std::string name)
{
    for (auto it = _functions.begin(); it != _functions.end(); ++it)
    {
        if (it->first == name) return it->second;
    }
    throw Exception("IntFileType::function() - function not found: " + name);
}

unsigned int IntFileType::function(unsigned int index)
{
    if (index >= _functionsName.size()) throw Exception("IntFileType::function() - function not found: " + std::to_string(index));
    return function(_functionsName.at(index));
}

}
