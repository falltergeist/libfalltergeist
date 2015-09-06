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
#include "../Ini/File.h"
#include "../Ini/Parser.h"
#include "../Txt/WorldmapFile.h"

// Third party includes

namespace libfalltergeist
{
namespace Txt
{


WorldmapFile::WorldmapFile(std::ifstream* stream) : Dat::Item(stream)
{
    _initialize();
}

WorldmapFile::WorldmapFile(Dat::Entry* datFileEntry) : Dat::Item(datFileEntry)
{
    _initialize();
}

void WorldmapFile::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    std::istream stream(this);
    Ini::Parser parser(stream);
    auto file = parser.parse();
    std::map<std::string, unsigned char> chanceNames;
    for (auto pairs : file->section("Data"))
    {
        auto& str = pairs.second.str();
        if (str[str.size() - 1] == '%')
        {
            chanceNames[pairs.first] = static_cast<unsigned char>(pairs.second.toInt());
        }
    }
    for (auto pairs : file->section("Data")["terrain_types"].toArray())
    {
        TerrainType terType = TerrainType();
        std::string sect = "Random Maps: " + pairs.first;
        if (file->hasSection(sect))
        {
            for (auto& ref : file->section(sect).listByMask("map_%02d"))
            {
                terType.randomMaps.push_back(ref.get().str());
            }
        }
        terrainTypes[pairs.first] = std::move(terType);
    }
    for (auto section : file->sections())
    {
        // TODO: implement
    }
}

}
}
