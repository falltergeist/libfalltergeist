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

#ifndef LIBFALLTERGEIST_PRO_FILE_H
#define LIBFALLTERGEIST_PRO_FILE_H

// C++ standard includes
#include <vector>

// libfalltergeist includes
#include "../Dat/Item.h"

// Third party includes

namespace libfalltergeist
{
namespace Pro
{

enum ObjectType
{
    TYPE_ITEM = 0,
    TYPE_CRITTER,
    TYPE_SCENERY,
    TYPE_WALL,
    TYPE_TILE,
    TYPE_MISC
};

enum ItemType
{
    TYPE_ITEM_ARMOR = 0,
    TYPE_ITEM_CONTAINER,
    TYPE_ITEM_DRUG,
    TYPE_ITEM_WEAPON,
    TYPE_ITEM_AMMO,
    TYPE_ITEM_MISC,
    TYPE_ITEM_KEY
};

enum SceneryType
{
    TYPE_SCENERY_DOOR = 0,
    TYPE_SCENERY_STAIRS,
    TYPE_SCENERY_ELEVATOR,
    TYPE_SCENERY_LADDER_BOTTOM,
    TYPE_SCENERY_LADDER_TOP,
    TYPE_SCENERY_GENERIC
};

enum DamageType
{
    DAMAGE_NORMAL = 0,
    DAMAGE_LASER,
    DAMAGE_FIRE,
    DAMAGE_PLASMA,
    DAMAGE_ELECTRICAL,
    DAMAGE_EMP,
    DAMAGE_EXPLOSION,
    DAMAGE_RADIATION,
    DAMAGE_POISON
};

class File : public Dat::Item
{

public:
    File(std::shared_ptr<Dat::Entry> datFileEntry);
    File(std::ifstream* stream);
    ~File();

    uint8_t soundId() const;

    int32_t PID() const;
    int32_t FID() const;
    int32_t scriptId() const;
    int32_t perk() const;
    int32_t inventoryFID() const;
    int32_t armorMaleFID() const;
    int32_t armorFemaleFID() const;

    uint32_t weaponAnimationCode() const;
    uint32_t weaponDamageMin() const;
    uint32_t weaponDamageMax() const;
    uint32_t weaponDamageType() const;
    uint32_t weaponRangePrimary() const;
    uint32_t weaponRangeSecondary() const;
    uint32_t weaponMinimumStrenght() const;
    uint32_t weaponActionCostPrimary() const;
    uint32_t weaponActionCostSecondary() const;
    uint32_t weaponBurstRounds() const;
    uint32_t weaponAmmoType() const;
    uint32_t weaponAmmoPID() const;
    uint32_t weaponAmmoCapacity() const;
    uint32_t armorClass() const;
    uint32_t typeId() const;
    uint32_t subtypeId() const;
    uint32_t messageId() const;
    uint32_t flags() const;
    uint32_t flagsExt() const;
    uint32_t weight() const;
    uint32_t critterHitPointsMax() const;
    uint32_t critterActionPoints() const;
    uint32_t critterArmorClass() const;
    uint32_t critterMeleeDamage() const;
    uint32_t critterCarryWeightMax() const;
    uint32_t critterSequence() const;
    uint32_t critterHealingRate() const;
    uint32_t critterCriticalChance() const;

    std::vector<uint32_t>* critterStats();
    std::vector<uint32_t>* critterStatsBonus();
    std::vector<uint32_t>* critterSkills();
    std::vector<uint32_t>* damageResist();
    std::vector<uint32_t>* damageThreshold();

protected:
    uint8_t _soundId = 0;

    int32_t _PID = -1;
    int32_t _FID = -1;
    int32_t _critterHeadFID = -1;
    int32_t _perk = -1;
    int32_t _SID = -1;
    int32_t _inventoryFID = -1;

    uint32_t _armorMaleFID = 0;
    uint32_t _armorFemaleFID = 0;
    uint32_t _armorClass = 0;
    uint32_t _weaponAnimationCode = 0;
    uint32_t _weaponDamageMin = 0;
    uint32_t _weaponDamageMax = 0;
    uint32_t _weaponDamageType = 0;
    uint32_t _weaponRangePrimary = 0;
    uint32_t _weaponRangeSecondary = 0;
    uint32_t _weaponMinimumStrenght = 0;
    uint32_t _weaponActionCostPrimary = 0;
    uint32_t _weaponActionCostSecondary = 0;
    uint32_t _weaponBurstRounds = 0;
    uint32_t _weaponAmmoType = 0;
    uint32_t _weaponAmmoPID = 0;
    uint32_t _weaponAmmoCapacity = 0;
    uint32_t _subtypeId = 0;
    uint32_t _messageId = 0;
    uint32_t _critterHitPointsMax = 0;
    uint32_t _critterActionPoints = 0;
    uint32_t _critterArmorClass = 0;
    uint32_t _critterMeleeDamage = 0;
    uint32_t _critterCarryWeightMax = 0;
    uint32_t _critterSequence = 0;
    uint32_t _critterHealingRate = 0;
    uint32_t _critterCriticalChance = 0;
    uint32_t _lightDistance = 0;
    uint32_t _lightIntencity = 0;
    uint32_t _flags = 0;
    uint32_t _flagsExt = 0;
    uint32_t _materialId = 0;
    uint32_t _containerSize = 0;
    uint32_t _weight = 0;
    uint32_t _basePrice = 0;

    std::vector<uint32_t> _critterStats = {0, 0, 0, 0, 0, 0, 0};
    std::vector<uint32_t> _critterStatsBonus = {0, 0, 0, 0, 0, 0, 0};
    std::vector<uint32_t> _critterSkills = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<uint32_t> _damageResist = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<uint32_t> _damageThreshold = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    virtual void _initialize();
};

}
}
#endif // LIBFALLTERGEIST_PRO_FILE_H
