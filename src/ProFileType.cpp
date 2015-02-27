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
#include "../src/ProFileType.h"

// Third party includes

namespace libfalltergeist
{

ProFileType::ProFileType(std::shared_ptr<DatFileEntry> datFileEntry) : DatFileItem(datFileEntry)
{
}

ProFileType::ProFileType(std::ifstream* stream) : DatFileItem(stream)
{
}

ProFileType::~ProFileType()
{
}

void ProFileType::_initialize()
{
    if (_initialized) return;
    DatFileItem::_initialize();
    DatFileItem::setPosition(0);

    *this >> _PID >> _messageId >> _FID;
    *this >> _lightDistance >> _lightIntencity >> _flags;

    switch (typeId())
    {
        case TYPE_TILE:
        case TYPE_MISC:
            break;
        default:
            *this >> _flagsExt;
            break;
    }

    switch (typeId())
    {
        case TYPE_ITEM:
        case TYPE_CRITTER:
        case TYPE_SCENERY:
        case TYPE_WALL:
            *this >> _SID;
            break;
        case TYPE_TILE:
        case TYPE_MISC:
            break;
    }

    switch (typeId())
    {
        case TYPE_ITEM:
        {
            *this >> _subtypeId;
            *this >> _materialId;
            *this >> _containerSize;
            *this >> _weight ;
            *this >> _basePrice;
            *this >> _inventoryFID;
            *this >> _soundId;

            switch (subtypeId())
            {
                case TYPE_ITEM_ARMOR:
                {
                    *this >> _armorClass; // Armor class
                    int uint32;
                    // Damage resist
                    for (unsigned int i = 0; i != 7; ++i)
                    {
                        *this >> uint32;
                        _damageResist.at(i) = uint32;
                    }
                    // Damage threshold
                    for (unsigned int i = 0; i != 7; ++i)
                    {
                        *this >> uint32;
                        _damageThreshold.at(i) = uint32;
                    }
                    *this >> _perk; // Perk
                    *this >> _armorMaleFID; // Male FID
                    *this >> _armorFemaleFID; // Female FID
                    break;
                }
                case TYPE_ITEM_CONTAINER:
                {
                    this->skipBytes(4); // max size
                    this->skipBytes(4); // containter flags
                    break;
                }
                case TYPE_ITEM_DRUG:
                {
                    this->skipBytes(4); // Stat0
                    this->skipBytes(4); // Stat1
                    this->skipBytes(4); // Stat2
                    this->skipBytes(4); // Stat0 ammount
                    this->skipBytes(4); // Stat1 ammount
                    this->skipBytes(4); // Stat2 ammount
                    // first delayed effest
                    this->skipBytes(4); // delay in game minutes
                    this->skipBytes(4); // Stat0 ammount
                    this->skipBytes(4); // Stat1 ammount
                    this->skipBytes(4); // Stat2 ammount
                    // second delayed effest
                    this->skipBytes(4); // delay in game minutes
                    this->skipBytes(4); // Stat0 ammount
                    this->skipBytes(4); // Stat1 ammount
                    this->skipBytes(4); // Stat2 ammount
                    this->skipBytes(4); // addiction chance
                    this->skipBytes(4); // addiction perk
                    this->skipBytes(4); // addiction delay
                    break;
                }
                case TYPE_ITEM_WEAPON:
                    *this >> _weaponAnimationCode;
                    *this >> _weaponDamageMin;
                    *this >> _weaponDamageMax;
                    *this >> _weaponDamageType;
                    *this >> _weaponRangePrimary;
                    *this >> _weaponRangeSecondary;
                    this->skipBytes(4); // Proj PID ??
                    *this >> _weaponMinimumStrenght;
                    *this >> _weaponActionCostPrimary;
                    *this >> _weaponActionCostSecondary;
                    this->skipBytes(4); // Crit Fail ??
                    *this >> _perk;
                    *this >> _weaponBurstRounds;
                    *this >> _weaponAmmoType;
                    *this >> _weaponAmmoPID;
                    *this >> _weaponAmmoCapacity;
                    *this >> _soundId;
                    break;
                case TYPE_ITEM_AMMO:
                    break;
                case TYPE_ITEM_MISC:
                    break;
                case TYPE_ITEM_KEY:
                    break;
            }
            break;
        }
        case TYPE_CRITTER:
        {
            *this >> _critterHeadFID;


            this->skipBytes(4); // ai packet number
            this->skipBytes(4); // team number
            this->skipBytes(4); // flags

            int uint32;
            for (unsigned int i = 0; i != 7; ++i)
            {
                *this >> uint32;
                _critterStats.at(i) = uint32;
            }
            *this   >> _critterHitPointsMax
                    >> _critterActionPoints
                    >> _critterArmorClass;
            this->skipBytes(4); // Unused
            *this   >> _critterMeleeDamage
                    >> _critterCarryWeightMax
                    >> _critterSequence
                    >> _critterHealingRate
                    >> _critterCriticalChance;
            this->skipBytes(4); // Better criticals

            // Damage threshold
            for (unsigned int i = 0; i != 7; ++i)
            {
                *this >> uint32;
                _damageThreshold.at(i) = uint32;
            }
            // Damage resist
            for (unsigned int i = 0; i != 9; ++i)
            {
                *this >> uint32;
                _damageResist.at(i) = uint32;
            }

            this->skipBytes(4); // age
            this->skipBytes(4); // sex

            for (unsigned int i = 0; i != 7; ++i)
            {
                *this >> uint32;
                _critterStatsBonus.at(i) = uint32;
            }

            this->skipBytes(4); // Bonus Health points
            this->skipBytes(4); // Bonus Action points
            this->skipBytes(4); // Bonus Armor class
            this->skipBytes(4); // Bonus Unused
            this->skipBytes(4); // Bonus Melee damage
            this->skipBytes(4); // Bonus Carry weight
            this->skipBytes(4); // Bonus Sequence
            this->skipBytes(4); // Bonus Healing rate
            this->skipBytes(4); // Bonus Critical chance
            this->skipBytes(4); // Bonus Better criticals

            this->skipBytes(4*8); // Bonus Damage threshold
            this->skipBytes(4*8); // Bonus Damage resistance

            this->skipBytes(4); // Bonus age
            this->skipBytes(4); // Bonus sex

            for (unsigned int i = 0; i != 18; ++i)
            {
                *this >> uint32;
                _critterSkills.at(i) = uint32;
            }

            break;

            this->skipBytes(4); // body type
            this->skipBytes(4); // experience for kill
            this->skipBytes(4); // kill type
            this->skipBytes(4); // damage type
        }
        case TYPE_SCENERY:
        {
            *this >> _subtypeId;
            *this >> _materialId;
            *this >> _soundId;
            switch(subtypeId())
            {
                case TYPE_SCENERY_DOOR:
                {
                    this->skipBytes(4); // walk thru flag
                    this->skipBytes(4); // unknown
                    break;
                }
                case TYPE_SCENERY_STAIRS:
                {
                    this->skipBytes(4); // DestTile && DestElevation
                    this->skipBytes(4); // DestElevation
                    break;
                }
                case TYPE_SCENERY_ELEVATOR:
                {
                    this->skipBytes(4); // Elevator type
                    this->skipBytes(4); // Elevator level
                    break;
                }
                case TYPE_SCENERY_LADDER_BOTTOM:
                case TYPE_SCENERY_LADDER_TOP:
                {
                    this->skipBytes(4); // DestTile && DestElevation
                    break;
                }
                case TYPE_SCENERY_GENERIC:
                {
                    this->skipBytes(4); // unknown
                }
            }

            break;
        }
        case TYPE_WALL:
        {
            *this >> _materialId;
            break;
        }
        case TYPE_TILE:
        {
            *this >> _materialId;
            break;
        }
        case TYPE_MISC:
        {
            this->skipBytes(4); // unknown
            break;
        }
    }

}

int ProFileType::PID()
{
    return _PID;
}

int ProFileType::FID()
{
    return _FID;
}

int ProFileType::typeId()
{
    _initialize();
    return (_PID & 0x0F000000) >> 24;
}

int ProFileType::subtypeId()
{
    _initialize();
    return _subtypeId;
}

unsigned int ProFileType::messageId()
{
    _initialize();
    return _messageId;
}

unsigned int ProFileType::flags()
{
    return _flags;
}

unsigned int ProFileType::flagsExt()
{
    _initialize();
    return _flagsExt;
}

int ProFileType::scriptId()
{
    _initialize();
    if (_SID == -1) return -1;
    return _SID & 0x0000FFFF;
}

std::vector<int>* ProFileType::critterStats()
{
    return &_critterStats;
}

std::vector<int>* ProFileType::critterStatsBonus()
{
    return &_critterStatsBonus;
}

std::vector<int>* ProFileType::critterSkills()
{
    return &_critterSkills;
}

std::vector<int>* ProFileType::damageResist()
{
    return &_damageResist;
}

std::vector<int>* ProFileType::damageThreshold()
{
    return &_damageThreshold;
}

int ProFileType::critterHitPointsMax()
{
    return _critterHitPointsMax;
}

int ProFileType::critterActionPoints()
{
    return _critterActionPoints;
}

int ProFileType::critterArmorClass()
{
    return _critterArmorClass;
}

int ProFileType::critterMeleeDamage()
{
    return _critterMeleeDamage;
}

unsigned int ProFileType::critterCarryWeightMax()
{
    return _critterCarryWeightMax;
}

int ProFileType::critterSequence()
{
    return _critterSequence;
}

int ProFileType::critterCriticalChance()
{
    return _critterCriticalChance;
}

int ProFileType::critterHealingRate()
{
    return _critterHealingRate;
}

unsigned int ProFileType::weight()
{
    return _weight;
}

void ProFileType::setWeight(unsigned int value)
{
    _weight = value;
}

int ProFileType::perk()
{
    return _perk;
}

unsigned int ProFileType::armorFemaleFID()
{
    return _armorFemaleFID;
}

unsigned int ProFileType::armorMaleFID()
{
    return _armorMaleFID;
}

unsigned int ProFileType::armorClass()
{
    return _armorClass;
}

unsigned int ProFileType::weaponAnimationCode()
{
    return _weaponAnimationCode;
}

unsigned int ProFileType::weaponDamageMin()
{
    return _weaponDamageMin;
}

unsigned int ProFileType::weaponDamageMax()
{
    return _weaponDamageMax;
}

unsigned int ProFileType::weaponDamageType()
{
    return _weaponDamageType;
}

unsigned int ProFileType::weaponRangePrimary()
{
    return _weaponRangePrimary;
}

unsigned int ProFileType::weaponRangeSecondary()
{
    return _weaponRangeSecondary;
}

unsigned int ProFileType::weaponMinimumStrenght()
{
    return _weaponMinimumStrenght;
}

unsigned int ProFileType::weaponActionCostPrimary()
{
    return _weaponActionCostPrimary;
}

unsigned int ProFileType::weaponActionCostSecondary()
{
    return _weaponActionCostSecondary;
}

unsigned int ProFileType::weaponBurstRounds()
{
    return _weaponBurstRounds;
}

unsigned int ProFileType::weaponAmmoType()
{
    return _weaponAmmoType;
}

unsigned int ProFileType::weaponAmmoPID()
{
    return _weaponAmmoPID;
}

unsigned int ProFileType::weaponAmmoCapacity()
{
    return _weaponAmmoCapacity;
}

unsigned char ProFileType::soundId() const
{
    return _soundId;
}

unsigned int ProFileType::inventoryFID()
{
    return _inventoryFID;
}

}
