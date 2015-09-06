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
#include "../Txt/MapsFile.h"

// Third party includes

namespace libfalltergeist
{
namespace Txt
{


MapsFile::MapsFile(std::ifstream* stream) : Dat::Item(stream)
{
    _initialize();
}

MapsFile::MapsFile(Dat::Entry* datFileEntry) : Dat::Item(datFileEntry)
{
    _initialize();
}

const std::vector<Map>& MapsFile::maps() const
{
    return _maps;
}

void MapsFile::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    std::istream stream(this);
    Ini::Parser parser(stream);
    auto file = parser.parse();
    for (auto section : file->sections())
    {
        Map map = Map();
        map.name = section["map_name"];
        map.lookupName = section["lookup_name"];
        map.music = section["music"];
        parser.toLower(map.music);
        for (auto pair : section["ambient_sfx"].toArray())
        {
            parser.toLower(pair.first);
            map.ambientSfx[pair.first] = static_cast<unsigned char>(pair.second.toInt());
        }
        map.saved = section["saved"].toBool();
        auto canRest = section["can_rest_here"].toArray();
        if (canRest.size() >= Map::NUM_ELEVATIONS)
        {
            for (int i = 0; i < Map::NUM_ELEVATIONS; i++)
            {
                map.canRestHere[i] = canRest[i].second.toBool();
            }
        }

        for (auto prop : section.listByMask("random_start_point_%d"))
        {
            MapStartPoint point = MapStartPoint();
            for (auto pair : prop.get().toArray())
            {
                if (pair.first == "elev")
                {
                    point.elevation = pair.second.toInt();
                }
                else if (pair.first == "tile_num")
                {
                    point.tileNum = pair.second.toInt();
                }
            }
            map.randomStartPoints.push_back(point);
        }

        _maps.push_back(map);
    }
}

}
}
