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

    std::cout << std::hex << this->position() << " Functions table size: " << std::dec << functionsTableSize << std::endl;

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
        _functionsOffsets.push_back(entryPoint);
        std::cout << "Function: name = 0x" << std::hex << nameOffset << " : entryPoint = 0x" << entryPoint << std::endl;
    }

    // IDENTIFICATORS TABLE
    unsigned int identificatorsTableSize;
    *this >> identificatorsTableSize;
    std::cout << std::hex << this->position() <<  "Identificators table size: " << std::dec << identificatorsTableSize << std::endl;

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

        _identificators.insert(std::make_pair(nameOffset, name));
        std::cout << "Identificator: " << std::hex << "0x" << nameOffset << " - " << name << std::endl;
    }

    for (auto it = functions.begin(); it != functions.end(); ++it)
    {
        _functions.insert(std::make_pair( it->second, _identificators.at(it->first)));
    }

    unsigned int signature; // must be 0xFFFFFFFF
    *this >> signature;
    std::cout << "Signature: " << std::hex << signature << std::endl;

    // STRINGS TABLE

    unsigned int stringsTableSize;
    *this >> stringsTableSize;

    if (stringsTableSize != 0xFFFFFFFF)
    {
        std::cout << std::hex << this->position() <<  "Strings table size: " << std::dec << stringsTableSize << std::endl;
        unsigned int j = 0;
        while (j < stringsTableSize)
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

            _strings.insert(std::make_pair(nameOffset, name));
            std::cout << "String: 0x"<< std::hex << nameOffset << " - " << name << std::endl;
        }

        *this >> signature;
    }
}

unsigned int IntFileType::function(std::string name)
{
    for (auto it = _functions.begin(); it != _functions.end(); ++it)
    {
        if (it->second == name) return it->first;
    }
    throw Exception("IntFileType::function(string) - function not found: " + name);
}

unsigned int IntFileType::function(unsigned int index)
{
    try
    {
        return _functionsOffsets.at(index);
    }
    catch (...)
    {
        throw Exception("IntFileType::function(int) - function not found: " + std::to_string(index));
    }
}

std::map<unsigned int, std::string>* IntFileType::identificators()
{
    return &_identificators;
}

std::map<unsigned int, std::string>* IntFileType::strings()
{
    return &_strings;
}

}
