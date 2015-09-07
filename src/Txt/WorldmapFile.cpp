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

    for (auto pairs : file->section("Data"))
    {
        auto& str = pairs.second.str();
        if (str[str.size() - 1] == '%')
        {
            chanceNames[pairs.first] = static_cast<unsigned char>(pairs.second.toInt());
        }
    }
    for (auto pair : file->section("Data")["terrain_types"].toArray())
    {
        TerrainType terType = TerrainType();
        terType.travelDelay = pair.second.toInt();
        std::string sect = "Random Maps: " + pair.first;
        if (file->hasSection(sect))
        {
            for (auto& ref : file->section(sect).listByMask("map_%02d"))
            {
                terType.randomMaps.push_back(ref.get().str());
            }
        }
        terrainTypes[pair.first] = std::move(terType);
    }
    numHorizontalTiles = file->section("Tile Data")["num_horizontal_tiles"].toInt();
    for (auto section : file->sections())
    {
        auto pos = section.name().find("Encounter:");
        if (pos == 0)
        {
            std::string name = section.name().substr(pos, std::string::npos);
            parser.trim(name);
            Encounter enc = Encounter();
            for (auto pair : section["position"].toArray())
            {
                parser.toLower(pair.first);
                if (pair.first.size() == 0)
                {
                    enc.position = pair.second.str();
                }
                else if (pair.first == "spacing")
                {
                    enc.spacing = pair.second.toInt();
                }
                else if (pair.first == "distance")
                {
                    enc.distance = _parseNumericExpression(pair.second);
                }
            }
            for (auto& ref : section.listByMask("type_%02d"))
            {
                enc.objects.push_back(_parseEncounterObject(ref.get()));
            }
            encounterTypes[name] = std::move(enc);
        }
        else if (section.name().find("Encounter Table") == 0)
        {
            EncounterTable table = EncounterTable();
            table.lookupName = section["lookup_name"];
            for (auto pair : section["maps"].toArray())
            {
                std::string mapName = pair.second.str();
                Ini::Parser::trim(mapName);
                table.maps.push_back(std::move(mapName));
            }
            for (auto& ref : section.listByMask("enc_%02d"))
            {
                table.encounters.push_back(_parseEncounterTableEntry(ref.get()));
            }
            encounterTables[table.lookupName] = std::move(table);
        }
        else if (section.name().find("Tile") == 0)
        {
            WorldmapTile tile = WorldmapTile();
            tile.artIdx = section["art_idx"].toInt();
            tile.encounterDifficulty = section["encounter_difficulty"].toInt();
            tile.walkMaskName = section["walk_mask_name"];
            for (int i = 0; i < WorldmapTile::SUBTILES_X; i++)
            {
                for (int j = 0; j < WorldmapTile::SUBTILES_Y; j++)
                {
                    tile.subtiles[i, j] = _parseSubtile(section[std::to_string(i) + "_" + std::to_string(j)]);
                }
            }
            tiles.push_back(std::move(tile));
        }
    }
}

EncounterObject WorldmapFile::_parseEncounterObject(const Ini::Value& val)
{
    EncounterObject obj = EncounterObject();
    for (auto pair : val.toArray())
    {
        Ini::Parser::toLower(pair.first);
        if (pair.first == "ratio")
        {
            obj.ratio = pair.second.toInt();
        }
        else if (pair.first == "pid")
        {
            obj.pid = pair.second.toInt();
        }
        else if (pair.first == "script")
        {
            obj.script = pair.second.toInt();
        }
        else if (pair.first == "item")
        {
            obj.items.push_back(_parseInventoryItem(pair.second.str()));
        }
        else if (pair.second.str() == "Dead")
        {
            obj.dead = true;
        }
        else if (pair.second.str().find("If(") != std::string::npos)
        {
            obj.condition = _parseCondition(pair.second.str());
        }
    }
    return obj;
}

InventoryItem WorldmapFile::_parseInventoryItem(const std::string& string)
{
    // @TODO: implement
    return Txt::InventoryItem();
}

EncounterTableEntry WorldmapFile::_parseEncounterTableEntry(const Ini::Value& string)
{
    // @TODO: implement
    return Txt::EncounterTableEntry();
}

EncounterGroup WorldmapFile::_parseEncounterGroup(const std::string& string)
{
    // @TODO: implement
    return Txt::EncounterGroup();
}

Condition WorldmapFile::_parseCondition(const std::string& string)
{
    // @TODO: implement
    return Condition();
}

LogicalExpression WorldmapFile::_parseLogicalExpression(const std::string& string)
{
    // @TODO: implement
    return Txt::LogicalExpression();
}

NumericExpression WorldmapFile::_parseNumericExpression(const std::string& string)
{
    // @TODO: implement
    return NumericExpression(NumericExpression::CONSTANT, Ini::Value("0"));
}

WorldmapSubtile WorldmapFile::_parseSubtile(const Ini::Value& value)
{
    WorldmapSubtile subtile = WorldmapSubtile();
    auto array = value.toArray();
    if (array.size() >= 6)
    {
        subtile.terrain = array[0].second;
        subtile.fill = (array[1].second.str() == "Fill_W")
                       ? WorldmapSubtile::Fill::FILL_W
                       : WorldmapSubtile::Fill::NO_FILL;
        subtile.morningChance = _chanceByName(array[2].second);
        subtile.afternoonChance = _chanceByName(array[3].second);
        subtile.nightChance = _chanceByName(array[4].second);
        subtile.encounterTable = array[5].second;
    }
    return subtile;
}

unsigned char WorldmapFile::_chanceByName(const std::string& name)
{
    auto it = chanceNames.find(name);
    if (it != chanceNames.end())
    {
        return *it;
    }
    return 0;
}

}
}
