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
#include "../src/DatFileEntry.h"

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

    unsigned int PID;
    unsigned int FID;

    *this >> PID >> _messageId >> FID;

    _objectTypeId = (PID & 0x0F000000) >> 28;
    _objectId = PID & 0x00000FFF;

    _frmTypeId = (FID & 0x0F000000) >> 28;
    _frmOffset = (FID & 0x00FF0000) >> 16;

    _frmId = FID & 0x0000FFFF;

    switch (_objectTypeId)
    {
        case TYPE_ITEM:
        {
            *this >> _lightDistance >> _lightIntencity;

            *this >> _flags >> _flagsExt;

            unsigned int SID;
            *this >> SID;
            _scriptTypeId = (SID & 0xFF000000) >> 24;
            _scriptId = SID & 0x0000FFFF;

            *this >> _objectSubtypeId;

            *this >> _materialId;
            *this >> _containerSize;

            *this >> _weight ;
            *this >> _basePrice;

            unsigned int FID;
            *this >> FID;
            _inventoryFrmTypeId = (FID & 0xFF000000) >> 24;
            _inventoryFrmTypeId = FID & 0x00FFFF;

            *this >> _soundId;

            switch (_objectSubtypeId)
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
            *this >> _lightDistance >> _lightIntencity;

            *this >> _flags >> _flagsExt;

            unsigned int SID;
            *this >> SID;
            _scriptTypeId = (SID & 0xFF000000) >> 24;
            _scriptId = SID & 0x0000FFFF;

            unsigned int FID;
            *this >> FID;
            _headFrmTypeId = (FID & 0xFF000000) >> 24;
            _headFrmId = FID & 0x0000FFFF;

            // more ...

            break;
        }
        case TYPE_SCENERY:
        {
            *this >> _lightDistance >> _lightIntencity;

            *this >> _flags >> _flagsExt;

            unsigned int SID;
            *this >> SID;
            _scriptTypeId = (SID & 0xFF000000) >> 24;
            _scriptId = SID & 0x0000FFFF;

            *this >> _objectSubtypeId;

            *this >> _materialId;

            *this >> _soundId;

            break;
        }
        case TYPE_WALL:
        {
            *this >> _lightDistance >> _lightIntencity;

            *this >> _flags >> _flagsExt;

            unsigned int SID;
            *this >> SID;
            _scriptTypeId = (SID & 0xFF000000) >> 24;
            _scriptId = SID & 0x0000FFFF;

            *this >> _materialId;
            break;
        }
        case TYPE_TILE:
        {
            *this >> _flags >> _flagsExt;

            this->skipBytes(4); //unknown

            *this >> _materialId;
            break;
        }
        case TYPE_MISC:
        {
            *this >> _lightDistance >> _lightIntencity;

            *this >> _flags >> _flagsExt;
            break;
        }
    }
}

unsigned int ProFileType::objectTypeId()
{
    _initialize();
    return _objectTypeId;
}

unsigned int ProFileType::objectSubtypeId()
{
    _initialize();
    return _objectSubtypeId;
}

int ProFileType::frmOffset()
{
    _initialize();
    return _frmOffset;
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

}
