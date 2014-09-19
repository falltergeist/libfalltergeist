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

#ifndef LIBFALLTERGEIST_PROFILETYPE_H
#define LIBFALLTERGEIST_PROFILETYPE_H

// C++ standard includes
#include <vector>

// libfalltergeist includes
#include "../src/DatFileItem.h"

// Third party includes

namespace libfalltergeist
{

class ProFileType : public DatFileItem
{
protected:
    int _PID;
    int _subtypeId;

    int _messageId;

    int _FID;

    int _critterHeadFID = -1;
    int _critterHitPointsMax = 0;
    int _critterActionPoints = 0;
    int _critterArmorClass = 0;
    int _critterMeleeDamage = 0;
    unsigned int _critterCarryWeightMax = 0;
    int _critterSequence = 0;
    int _critterHealingRate = 0;
    int _critterCriticalChance = 0;

    std::vector<int> _critterStats = {0, 0, 0, 0, 0, 0, 0};
    std::vector<int> _critterStatsBonus = {0, 0, 0, 0, 0, 0, 0};
    std::vector<int> _critterSkills = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<int> _damageResist = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<int> _damageThreshold = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    int _perk = -1;
    unsigned int _armorMaleFID = 0;
    unsigned int _armorFemaleFID = 0;
    unsigned int _armorClass = 0;

    unsigned int _weaponAnimationCode = 0;
    unsigned int _weaponDamageMin = 0;
    unsigned int _weaponDamageMax = 0;
    unsigned int _weaponDamageType = 0;
    unsigned int _weaponRangePrimary = 0;
    unsigned int _weaponRangeSecondary = 0;
    unsigned int _weaponMinimumStrenght = 0;
    unsigned int _weaponActionCostPrimary = 0;
    unsigned int _weaponActionCostSecondary = 0;
    unsigned int _weaponBurstRounds = 0;
    unsigned int _weaponAmmoType = 0;
    unsigned int _weaponAmmoPID = 0;
    unsigned int _weaponAmmoCapacity = 0;



    unsigned int _lightDistance;
    unsigned int _lightIntencity;

    unsigned int _flags;
    unsigned int _flagsExt;

    int _SID;

    unsigned int _materialId;
    unsigned int _containerSize;
    unsigned int _weight = 0;
    unsigned int _basePrice;

    unsigned int _inventoryFID;

    unsigned char _soundId;

    virtual void _initialize();
public:
    enum { TYPE_ITEM = 0, TYPE_CRITTER, TYPE_SCENERY, TYPE_WALL, TYPE_TILE, TYPE_MISC };
    enum { TYPE_ITEM_ARMOR = 0, TYPE_ITEM_CONTAINER, TYPE_ITEM_DRUG, TYPE_ITEM_WEAPON, TYPE_ITEM_AMMO, TYPE_ITEM_MISC, TYPE_ITEM_KEY };
    enum { TYPE_SCENERY_DOOR = 0, TYPE_SCENERY_STAIRS, TYPE_SCENERY_ELEVATOR, TYPE_SCENERY_LADDER_BOTTOM, TYPE_SCENERY_LADDER_TOP, TYPE_SCENERY_GENERIC };
    enum { DAMAGE_NORMAL = 0, DAMAGE_LASER, DAMAGE_FIRE, DAMAGE_PLASMA, DAMAGE_ELECTRICAL, DAMAGE_EMP, DAMAGE_EXPLOSION, DAMAGE_RADIATION, DAMAGE_POISON };

    ProFileType(std::shared_ptr<DatFileEntry> datFileEntry);
    ProFileType(std::ifstream* stream);
    ~ProFileType();

    int PID();
    int FID();

    int typeId();
    int subtypeId();
    int scriptId();
    unsigned int messageId();
    unsigned int flags();
    unsigned int flagsExt();

    unsigned int weight();
    void setWeight(unsigned int value);

    int perk();

    unsigned int inventoryFID();

    int critterHitPointsMax();
    int critterActionPoints();
    int critterArmorClass();
    int critterMeleeDamage();
    unsigned int critterCarryWeightMax();
    int critterSequence();
    int critterHealingRate();
    int critterCriticalChance();

    std::vector<int>* critterStats();
    std::vector<int>* critterStatsBonus();
    std::vector<int>* critterSkills();
    std::vector<int>* damageResist();
    std::vector<int>* damageThreshold();

    unsigned int armorMaleFID();
    unsigned int armorFemaleFID();
    unsigned int armorClass();

    unsigned int weaponAnimationCode();
    unsigned int weaponDamageMin();
    unsigned int weaponDamageMax();
    unsigned int weaponDamageType();
    unsigned int weaponRangePrimary();
    unsigned int weaponRangeSecondary();
    unsigned int weaponMinimumStrenght();
    unsigned int weaponActionCostPrimary();
    unsigned int weaponActionCostSecondary();
    unsigned int weaponBurstRounds();
    unsigned int weaponAmmoType();
    unsigned int weaponAmmoPID();
    unsigned int weaponAmmoCapacity();


};
}

#endif // LIBFALLTERGEIST_PROFILETYPE_H
