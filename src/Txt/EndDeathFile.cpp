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

// Libfalltergeist includes
#include "../Txt/CSVParser.h"
#include "../Txt/EndDeathFile.h"

// Third party includes


namespace libfalltergeist
{
namespace Txt
{


EndDeathFile::EndDeathFile(std::ifstream* stream) : BaseFile(stream)
{
    _initialize();
}

EndDeathFile::EndDeathFile(Dat::Entry* datFileEntry) : BaseFile(datFileEntry)
{
    _initialize();
}

const std::list<EndDeath>& EndDeathFile::items() const
{
    return _items;
}

void EndDeathFile::_parseText(std::istream& istr)
{
    CSVParser parser(istr);
    auto csv = parser.parse();
    for (auto& row : *csv)
    {
        EndDeath item;
        item.globalVar = row[0].toInt();
        item.minValue = row[1].toInt();
        item.worldAreaKnown = row[2].toInt();
        item.worldAreaNotKnown = row[3].toInt();
        item.minLevel = row[4].toInt();
        item.chance = static_cast<unsigned char>(row[5].toInt());
        item.narratorFile = row[6].str();
        _items.push_back(std::move(item));
    }
}

}
}