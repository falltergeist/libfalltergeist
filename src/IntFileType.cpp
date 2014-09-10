/*
 * Copyright 2012-2014 Falltergeist Developers.
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

IntFileType::IntFileType(std::shared_ptr<DatFileEntry> datFileEntry) : DatFileItem(datFileEntry)
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


    // FUNCTIONS TABLE
    setPosition(42);
    unsigned int tableSize;
    *this >> tableSize;

    // @todo Delete this line
    std::cout << std::hex << this->position() << " Functions table size: " << std::dec << tableSize << std::endl;

    std::map<unsigned int, unsigned int> functions;
    for (unsigned int i = 0; i != tableSize; ++i)
    {
        unsigned int nameOffset;
        unsigned int entryPoint;
        *this >> nameOffset;
        skipBytes(12);
        *this >> entryPoint;
        skipBytes(4);
        functions.insert(std::make_pair(nameOffset, entryPoint));
        _functionsOffsets.push_back(entryPoint); // to find function entry point by number
        // @todo Delete this line
        std::cout << "Function: nameOffset - 0x"<< std::hex << nameOffset << " entryPoint - " << entryPoint << std::endl;
    }

    // IDENTIFICATORS TABLE
    *this >> tableSize;
    // @todo Delete this line
    std::cout << std::hex << this->position() <<  "Identificators table size: " << std::dec << tableSize << std::endl;

    unsigned int j = 0;
    while (j < tableSize)
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
        _identificators.insert(std::make_pair(nameOffset, name)); // names of functions and variables
        // @todo Delete this line
        std::cout << "Identificator: 0x"<< std::hex << nameOffset << " - " << name << std::endl;
    }

    this->skipBytes(4); // signature 0xFFFFFFFF

    for (auto it = functions.begin(); it != functions.end(); ++it)
    {
        _functions.insert(std::make_pair( it->second, _identificators.at(it->first))); // to access functions by name
    }


    // STRINGS TABLE

    *this >> tableSize;

    if (tableSize != 0xFFFFFFFF)
    {
        // @todo Delete this line
        std::cout << std::hex << this->position() <<  "Strings table size: " << std::dec << tableSize << std::endl;
        unsigned int j = 0;
        while (j < tableSize)
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

            // @todo Delete this line
            std::cout << "String: 0x"<< std::hex << nameOffset << " - " << name << std::endl;
        }
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
