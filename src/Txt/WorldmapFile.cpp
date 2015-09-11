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
#include <sstream>

// Libfalltergeist includes
#include "../Ini/File.h"
#include "../Ini/Parser.h"
#include "../Txt/Lexer.h"
#include "../Txt/WorldmapFile.h"

// Third party includes

namespace libfalltergeist
{
namespace Txt
{

const char* NumericExpression::CONSTANT    = "const";          // a numeric constant
const char* NumericExpression::PLAYER      = "Player";         // a value of player stat, perk, trait or skill
const char* NumericExpression::TIME_OF_DAY = "time_of_day";    // returns current hour (0 - 23)
const char* NumericExpression::GLOBAL      = "Global";         // game global variable value
const char* NumericExpression::RAND        = "Rand";           // a random value between 0 and 99


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
        const std::string encStr = "Encounter:";
        auto pos = section.name().find(encStr);
        if (pos == 0)
        {
            std::string name = section.name().substr(encStr.size(), std::string::npos);
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
                    std::istringstream istr(pair.second);
                    enc.distance = _parseNumericExpression(istr);
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
        else if (section.name().find("Tile") == 0 && section.name() != "Tile Data")
        {
            WorldmapTile tile = WorldmapTile();
            tile.artIdx = section["art_idx"].toInt();
            tile.encounterDifficulty = section["encounter_difficulty"].toInt();
            tile.walkMaskName = section["walk_mask_name"];
            for (int i = 0; i < WorldmapTile::SUBTILES_X; i++)
            {
                for (int j = 0; j < WorldmapTile::SUBTILES_Y; j++)
                {
                    tile.subtiles[i][j] = _parseSubtile(section[std::to_string(i) + "_" + std::to_string(j)]);
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
        else if (pair.first == "distance")
        {
            obj.distance = pair.second.toInt();
        }
        else if (pair.first == "item")
        {
            try
            {
                obj.items.push_back(_parseInventoryItem(pair.second.str()));
            }
            catch (std::ios::failure) {} // @TODO: log warning
        }
        else if (pair.second.str() == "Dead")
        {
            obj.dead = true;
        }
        else if (pair.second.str().find("If") != std::string::npos)
        {
            try
            {
                obj.condition = _parseCondition(pair.second.str());
            }
            catch (std::ios::failure) {} // @TODO: log warning
        }
    }
    return obj;
}

InventoryItem WorldmapFile::_parseInventoryItem(std::string value)
{
    InventoryItem item;
    Ini::Parser::toLower(value);
    std::istringstream istr(value);
    istr.exceptions(std::ios_base::failbit);
    _parseRange(istr, item.minCount, item.maxCount);
    istr >> item.pid;
    if (value.rfind("wielded") != std::string::npos)
    {
        item.wielded = true;
    }
    return item;
}

EncounterTableEntry WorldmapFile::_parseEncounterTableEntry(const Ini::Value& value)
{
    EncounterTableEntry entry;
    for (auto pair : value.toArray())
    {
        Ini::Parser::toLower(pair.first);
        if (pair.first == "chance")
        {
            entry.chance = (unsigned char)pair.second.toInt();
        }
        else if (pair.first == "counter")
        {
            entry.counter = pair.second.toInt();
        }
        else if (pair.first == "map")
        {
            entry.map = pair.second;
        }
        else if (pair.second.str() == "Special")
        {
            entry.isSpecial = true;
        }
        else if (pair.first == "enc")
        {
            // main encounter definition...
            std::istringstream istr(pair.second.str());
            istr.exceptions(std::ios::failbit);
            std::string action;
            do
            {
                try
                {
                    entry.team1.push_back(_parseEncounterGroup(istr));
                    //while (istr.get() == ' ') {}      istr.unget();
                    istr >> action;
                }
                catch (std::ios::failure)
                {
                    action == "";
                }
            }
            while (action == "AND");

            if (action == "AMBUSH")
            {
                entry.action = EncounterTableEntry::Action::AMBUSH_PLAYER;
            }
            else if (action == "FIGHTING")
            {
                do
                {
                    entry.team2.push_back(_parseEncounterGroup(istr));
                    istr >> action;
                }
                while (action == "AND");
            }
        }
        else if (pair.second.str().find("If") == 0)
        {
            entry.condition = _parseCondition(pair.second);
        }
    }
    return entry;
}

EncounterGroup WorldmapFile::_parseEncounterGroup(std::istringstream& istr)
{
    EncounterGroup grp;
    _parseRange(istr, grp.minCount, grp.maxCount);
    istr >> grp.encounterType;
    return grp;
}

Condition WorldmapFile::_parseCondition(const std::string& value)
{
    Condition cond;
    std::istringstream istr(value);
    istr.exceptions(std::ios::failbit);
    std::string logicalOperator;
    do
    {
        cond.push_back(_parseLogicalExpression(istr));
        try
        {
            istr >> logicalOperator;
        }
        catch (std::ios::failure)
        {
            break;
        }
        Ini::Parser::toLower(logicalOperator);
    }
    while (logicalOperator == "And");

    return cond;
}

LogicalExpression WorldmapFile::_parseLogicalExpression(std::istringstream& istr)
{
    LogicalExpression exp;
    std::string token;
    std::getline(istr, token, '(');
    Ini::Parser::toLower(token);
    Ini::Parser::rtrim(token);
    if (token != "if")
    {
        throw std::ios::failure("Invalid logical expression");
    }
    exp._leftOperand = _parseNumericExpression(istr);
    while (istr.get() == ' ') {}
    istr.unget();
    auto ch = istr.get();
    if (ch == '>' || ch == '<' || ch == '=')
    {
        if (ch == '>')
        {
            if (istr.get() == '=')
            {
                exp._operator = LogicalExpression::Operator::GTE;
            }
            else
            {
                exp._operator = LogicalExpression::Operator::GT;
                istr.unget();
            }
        }
        else if (ch == '<')
        {
            if (istr.get() == '=')
            {
                exp._operator = LogicalExpression::Operator::LTE;
            }
            else
            {
                exp._operator = LogicalExpression::Operator::LT;
                istr.unget();
            }
        }
        else
        {
            exp._operator = LogicalExpression::Operator::EQ;
        }
        istr >> exp._rightOperand;
    }
    else
    {
        istr.unget();
    }
    std::getline(istr, token, ')');
    return exp;
}

NumericExpression WorldmapFile::_parseNumericExpression(std::istringstream& istr)
{
    NumericExpression exp = NumericExpression();
    exp.func = "";
    char ch = (char)istr.get();
    while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')
    {
        exp.func.push_back(ch);
        ch = (char)istr.get();
    }
    istr.unget();
    if (exp.func.size() == 0)
    {
        exp.func = NumericExpression::CONSTANT;
    }
    std::string arg;
    if (istr.get() == '(')
    {
        std::getline(istr, arg, ')');
    }
    else
    {
        arg = "";
        istr.unget();
    }
    exp.arg = Ini::Value(arg);
    return exp;
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

void WorldmapFile::_parseRange(std::istringstream& istr, unsigned int& min, unsigned int& max)
{
    if (istr.get() == '(')
    {
        istr >> min;
        if (istr.get() == '-')
        {
            istr >> max;
        }
        else
        {
            istr.unget();
            max = min;
        }
        if (istr.get() != ')')
        {
            throw std::ios::failure("')' expected");
        }
    }
    else
    {
        istr.unget();
        min = max = 1;
    }
}

unsigned char WorldmapFile::_chanceByName(std::string name)
{
    Ini::Parser::toLower(name);
    auto it = chanceNames.find(name);
    if (it != chanceNames.end())
    {
        return it->second;
    }
    return 0;
}

}
}
