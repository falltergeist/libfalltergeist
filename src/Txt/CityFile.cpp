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
#include "../Txt/CityFile.h"

// Third party includes

namespace libfalltergeist
{
namespace Txt
{


CityFile::CityFile(std::ifstream* stream) : Dat::Item(stream)
{
    _initialize();
}

CityFile::CityFile(Dat::Entry* datFileEntry) : Dat::Item(datFileEntry)
{
    _initialize();
}

const std::vector<City>& CityFile::cities() const
{
    return _cities;
}

City::Size CityFile::_sizeByName(std::string name) const
{
    Ini::Parser::toLower(name);
    if (name == "small")
    {
        return City::Size::Small;
    }
    else if (name == "medium")
    {
        return City::Size::Medium;
    }
    else
    {
        return City::Size::Large;
    }
}

void CityFile::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    std::istream stream(this);
    Ini::Parser parser(stream);
    auto file = parser.parse();
    for (auto sec : file->sections())
    {
        City city;
        city.name = sec.second["area_name"];
        auto coords = parser.parseArray(sec.second["world_pos"]);
        if (coords.size() >= 2)
        {
            city.worldX = coords[0].second.toInt();
            city.worldY = coords[1].second.toInt();
        }
        city.startState = sec.second["start_state"].toBool();
        city.size = _sizeByName(sec.second["size"]);
        city.townMapArtIdx = sec.second["townmap_art_idx"].toInt();
        city.townMapLabelArtIdx = sec.second["townmap_label_art_idx"].toInt();
        int i = 0;
        std::string entrKey = "entrance_0";
        while (sec.second.hasProperty(entrKey))
        {
            auto entranceArray = sec.second.propertyArray(entrKey);
            if (entranceArray.size() >= 7)
            {
                CityEntrance entrance;
                entrance.startState = entranceArray[0].second.toBool();
                entrance.townMapX = entranceArray[1].second.toInt();
                entrance.townMapY = entranceArray[2].second.toInt();
                entrance.mapName = entranceArray[3].second.str();
                entrance.elevation = entranceArray[4].second.toInt();
                entrance.tileNum = entranceArray[5].second.toInt();
                entrance.orientation = entranceArray[6].second.toInt();
                city.entrances.push_back(entrance);
            }
            entrKey = "entrance_" + (++i);
        }
        _cities.push_back(city);
    }
}

}
}
