/*
 * Copyright 2012-2015 Falltergeist Developers.
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

// libfalltergeist includes
#include "../Int/File.h"
#include "../Exception.h"

// Third party includes

namespace libfalltergeist
{
namespace Int
{

File::File(std::shared_ptr<Dat::Entry> datFileEntry) : Dat::Item(datFileEntry)
{
}

File::File(std::ifstream* stream) : Dat::Item(stream)
{
}

File::~File()
{
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);


    // FUNCTIONS TABLE
    setPosition(42);
    unsigned int tableSize;
    *this >> tableSize;

    // @todo Delete this line
    //std::cout << std::hex << this->position() << " Functions table size: " << std::dec << tableSize << std::endl;

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
        //std::cout << "Function: nameOffset - 0x"<< std::hex << nameOffset << " entryPoint - " << entryPoint << std::endl;
    }

    // IDENTIFICATORS TABLE
    *this >> tableSize;
    // @todo Delete this line
    //std::cout << std::hex << this->position() <<  "Identificators table size: " << std::dec << tableSize << std::endl;

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
        _identifiers.insert(std::make_pair(nameOffset, name)); // names of functions and variables
        // @todo Delete this line
        //std::cout << "Identificator: 0x"<< std::hex << nameOffset << " - " << name << std::endl;
    }

    this->skipBytes(4); // signature 0xFFFFFFFF

    for (auto it = functions.begin(); it != functions.end(); ++it)
    {
        _functions.insert(std::make_pair( it->second, _identifiers.at(it->first))); // to access functions by name
    }


    // STRINGS TABLE

    *this >> tableSize;

    if (tableSize != 0xFFFFFFFF)
    {
        // @todo Delete this line
        //std::cout << std::hex << this->position() <<  "Strings table size: " << std::dec << tableSize << std::endl;
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
            //std::cout << "String: 0x"<< std::hex << nameOffset << " - " << name << std::endl;
        }
    }
}

unsigned int File::function(std::string name)
{
    for (auto it = _functions.begin(); it != _functions.end(); ++it)
    {
        if (it->second == name) return it->first;
    }
    throw Exception("File::function(string) - function not found: " + name);
}

unsigned int File::function(unsigned int index)
{
    try
    {
        return _functionsOffsets.at(index);
    }
    catch (...)
    {
        throw Exception("File::function(int) - function not found: " + std::to_string(index));
    }
}

std::map<unsigned int, std::string>* File::identifiers()
{
    return &_identifiers;
}

std::map<unsigned int, std::string>* File::strings()
{
    return &_strings;
}

std::map<unsigned int, std::string>* File::functions()
{
    return &_functions;
}

}
}
