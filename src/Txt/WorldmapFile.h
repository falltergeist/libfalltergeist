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

#ifndef LIBFALLTERGEIST_TXT_WORLDMAPFILE_H
#define LIBFALLTERGEIST_TXT_WORLDMAPFILE_H

// C++ standard includes
#include <vector>

// Libfalltergeist includes
#include "../Dat/Item.h"
#include "../Ini/Value.h"

// Third party includes

namespace libfalltergeist
{
namespace Txt
{

class ConditionFactor
{
public:
    ConditionFactor(const std::string& func, const Ini::Value& arg) : _func(func), _arg(arg)
    {
    }

    enum class Func
    {
        CONSTANT = 1,
        PLAYER,
        ENCOUNTER,
        TIME,
        GLOBAL,
        RAND
    };

private:
    std::string _func;
    Ini::Value _arg;
};

class ConditionTerm
{
public:
    enum class Operator
    {
        EQ, NE, GT, LT, GTE, LTE
    };

private:
    Operator _operator;
    ConditionFactor _leftOperand;
    ConditionFactor _rightOperand;
};

// Conditions consist of "subconditions" (Terms), delimited by "And"
typedef std::vector<ConditionTerm> Condition;


struct EncounterPosition
{
    std::string type;
    int spacing;
    ConditionFactor distance;
};

struct InventoryItem
{
    int pid;
    bool wielded;
    int minCount;
    int maxCount;
};

struct EncounterEntry
{
    int pid;
    int ratio;
    int script;
    bool dead = false;
    std::vector<InventoryItem> items;
    Condition condition;
};

/**
 *
 */
struct Encounter
{
    int teamNum;
    EncounterPosition position;
    std::vector<EncounterEntry> entries;
};

struct EncounterGroup
{
    std::string encounterType;
    int minCount;
    int maxCount;
};

struct EncounterTableEntry
{
    /**
     * True for "FIGHTING", false for "AMBUSH Player"
     */
    bool isFighting = false;
    /**
     * True for special encounters
     */
    bool isSpecial = false;
    /**
     * Force specific map for this encounter
     */
    std::string map;
    /**
     * Encounter chance in %
     */
    unsigned char chance = 0;
    int counter = -1;
    Condition condition;
    std::vector<EncounterGroup> team1;
    // used only when FIGHTING
    std::vector<EncounterGroup> team2;
};

struct EncounterTable
{
    std::string lookupName;
    std::vector<std::string> maps;
    std::vector<EncounterTableEntry> encounters;
};

struct TerrainType
{
    int travelDelay;
    std::vector<std::string> randomMaps;
};

struct WorldmapSubtile
{
    enum class Fill
    {
        FILL_W, NO_FILL
    };
    std::string terrain;
    Fill fill;
    unsigned char morningChance;
    unsigned char afternoonChance;
    unsigned char nightChance;
    std::string encounterTable;
};

struct WorldmapTile
{
    static const char SUBTILES_X = 7;
    static const char SUBTILES_Y = 6;
    int artIdx;
    int encounterDifficulty;
    std::string walkMaskName;
    WorldmapSubtile subtiles[SUBTILES_X, SUBTILES_Y];
};

/**
 * @brief WORLDMAP.TXT
 */
class WorldmapFile : public Dat::Item
{
public:
    WorldmapFile(std::ifstream* stream);
    WorldmapFile(Dat::Entry* datFileEntry);

    int numHorizontalTiles;

    std::map<std::string, TerrainType> terrainTypes;
    std::map<std::string, Encounter> encounterTypes;
    std::map<std::string, EncounterTable> encounterTables;

protected:

    void _initialize() override;
};

}
}




#endif //LIBFALLTERGEIST_TXT_WORLDMAPFILE_H
