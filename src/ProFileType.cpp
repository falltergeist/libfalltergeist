/*
 * Copyright 2012-2013 Falltergeist Developers.
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

ProFileType::ProFileType(DatFileEntry* datFileEntry) : DatFileItem(datFileEntry)
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

    switch (typeId())
    {
        case TYPE_TILE:
            break;
        default:
            *this >> _lightDistance >> _lightIntencity;
            break;
    }

    *this >> _flags >> _flagsExt;

    switch (typeId())
    {
        case TYPE_ITEM:
        case TYPE_CRITTER:
        case TYPE_SCENERY:
        case TYPE_WALL:
            int SID;
            *this >> SID;
            if (SID != -1)
            {
                _scriptTypeId = (SID & 0x0F000000) >> 24;
                _scriptId = SID & 0x0000FFFF;
            }
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
                    // armorClass 4
                    // damageResistNormal 4
                    // damageResistLaser 4
                    // damageResistFire 4
                    // damageResistPlasma 4
                    // damageResistElectrical 4
                    // damageResistEmp 4
                    // damageResistExplosion 4
                    // damageThresholdNormal 4
                    // damageThresholdLaser 4
                    // damageThresholdFire 4
                    // damageThresholdPlasma 4
                    // damageThresholdElectrical 4
                    // damageThresholdEmp 4
                    // damageThresholdExplosion 4
                    // perk 4
                    // male FID
                    // female FID
                    break;
                case TYPE_ITEM_CONTAINER:
                    // max size 4
                    // containerFlags 4
                    break;
                case TYPE_ITEM_DRUG:
                    break;
                case TYPE_ITEM_WEAPON:
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
            this->skipBytes(4); // Health points
            this->skipBytes(4); // Action points
            this->skipBytes(4); // Armor class
            this->skipBytes(4); // Unused
            this->skipBytes(4); // Melee damage
            this->skipBytes(4); // Carry weight
            this->skipBytes(4); // Sequence
            this->skipBytes(4); // Healing rate
            this->skipBytes(4); // Critical chance
            this->skipBytes(4); // Better criticals

            this->skipBytes(4*8); // Damage threshold
            this->skipBytes(4*8); // Damage resistance

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

            break;
        }
        case TYPE_WALL:
        {
            *this >> _materialId;
            break;
        }
        case TYPE_TILE:
        {
            this->skipBytes(4); //unknown
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

unsigned int ProFileType::flagsExt()
{
    _initialize();
    return _flagsExt;
}

int ProFileType::scriptId()
{
    _initialize();
    return _scriptId;
}

}
