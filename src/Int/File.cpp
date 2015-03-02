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
#include "../Int/Procedure.h"
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
    for (auto procedure : _procedures)
    {
        delete procedure;
    }
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    // Initialization code goes here
    setPosition(42);

    // Procedures table
    uint32_t proceduresCount = uint32();

    std::vector<uint32_t> procedureNameOffsets;

    for (unsigned i = 0; i != proceduresCount; ++i)
    {
        auto procedure = new Procedure();

        procedureNameOffsets.push_back(uint32());
        procedure->setFlags(uint32());
        procedure->setDelay(uint32());
        procedure->setConditionOffset(uint32());
        procedure->setBodyOffset(uint32());
        procedure->setArgumentsCounter(uint32());

        _procedures.push_back(procedure);
    }

    // Identificators table
    uint32_t tableSize = uint32();
    unsigned j = 0;
    while (j < tableSize)
    {
        uint16_t nameLength = uint16();
        j += 2;

        uint32_t nameOffset = j + 4;
        std::string name;
        for (unsigned i = 0; i != nameLength; ++i, ++j)
        {
            uint8_t ch = uint8();
            if (ch != 0) name.push_back(ch);
        }

        _identifiers.insert(std::make_pair(nameOffset, name)); // names of functions and variables
    }

    this->skipBytes(4); // signature 0xFFFFFFFF

    for (unsigned i = 0; i != procedureNameOffsets.size(); ++i)
    {
        _procedures.at(i)->setName(_identifiers.at(procedureNameOffsets.at(i)));
    }

    // STRINGS TABLE
    uint32_t stringsTable = uint32();

    if (stringsTable != 0xFFFFFFFF)
    {
        uint32_t j = 0;
        while (j < stringsTable)
        {
            uint16_t length = uint16();
            j += 2;
            uint32_t nameOffset = j + 4;
            std::string name;
            for (unsigned i = 0; i != length; ++i, ++j)
            {
                uint8_t ch = uint8();
                if (ch != 0) name.push_back(ch);
            }
            _strings.insert(std::make_pair(nameOffset, name));
        }
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

std::vector<Procedure*>* File::procedures()
{
    return &_procedures;
}

Procedure* File::procedure(std::string name)
{
    for (auto procedure : _procedures)
    {
        if (procedure->name() == name)
        {
            return procedure;
        }
    }
    return 0;
}


}
}
