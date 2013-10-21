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
#include "../src/DatFileItem.h"

// Third party includes

namespace libfalltergeist
{

ProFileType::ProFileType(DatFileItem * datFileItem)
{
    _datFileItem = datFileItem;

    _objectSubtypeId = 0;

    open();
}

ProFileType::~ProFileType()
{
}


DatFileItem * ProFileType::datFileItem()
{
    return _datFileItem;
}

void ProFileType::open()
{
    DatFileItem& item = *datFileItem();
    item.setPosition(0);

    unsigned int PID;
    item >> PID;

    _objectTypeId = (PID & 0x0F000000) >> 28;
    _objectId = PID & 0x00000FFF;


    item >> _messageId;


    unsigned int FID;
    item >> FID;

    _frmTypeId = (FID & 0x0F000000) >> 28;
    _frmOffset = (FID & 0x00FF0000) >> 16;

    _frmId = FID & 0x0000FFFF;


    switch (_objectTypeId)
    {
        case TYPE_ITEM:
        {
            item >> _lightDistance >> _lightIntencity;

            item >> _flags >> _flagsExt;

            unsigned int SID;
            item >> SID;
            _scriptTypeId = (SID & 0xFF000000) >> 24;
            _scriptId = SID & 0x0000FFFF;

            item >> _objectSubtypeId;

            item >> _materialId;
            item >> _containerSize;

            item >> _weight ;
            item >> _basePrice;

            unsigned int FID;
            item >> FID;
            _inventoryFrmTypeId = (FID & 0xFF000000) >> 24;
            _inventoryFrmTypeId = FID & 0x00FFFF;

            item >> _soundId;

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
            item >> _lightDistance >> _lightIntencity;

            item >> _flags >> _flagsExt;

            unsigned int SID;
            item >> SID;
            _scriptTypeId = (SID & 0xFF000000) >> 24;
            _scriptId = SID & 0x0000FFFF;

            unsigned int FID;
            _headFrmTypeId = (FID & 0xFF000000) >> 24;
            _headFrmId = FID & 0x0000FFFF;

            // more ...

            break;
        }
        case TYPE_SCENERY:
        {
            item >> _lightDistance >> _lightIntencity;

            item >> _flags >> _flagsExt;

            unsigned int SID;
            item >> SID;
            _scriptTypeId = (SID & 0xFF000000) >> 24;
            _scriptId = SID & 0x0000FFFF;

            item >> _objectSubtypeId;

            item >> _materialId;

            item >> _soundId;

            break;
        }
        case TYPE_WALL:
        {
            item >> _lightDistance >> _lightIntencity;

            item >> _flags >> _flagsExt;

            unsigned int SID;
            item >> SID;
            _scriptTypeId = (SID & 0xFF000000) >> 24;
            _scriptId = SID & 0x0000FFFF;

            item >> _materialId;
            break;
        }
        case TYPE_TILE:
        {
            item >> _flags >> _flagsExt;

            item.skipBytes(4); //unknown

            item >> _materialId;
            break;
        }
        case TYPE_MISC:
        {
            item >> _lightDistance >> _lightIntencity;

            item >> _flags >> _flagsExt;
            break;
        }
    }
}

unsigned int ProFileType::objectTypeId()
{
    return _objectTypeId;
}

unsigned int ProFileType::objectSubtypeId()
{
    return _objectSubtypeId;
}

int ProFileType::frmOffset()
{
    return _frmOffset;
}

unsigned int ProFileType::messageId()
{
    return _messageId;
}

unsigned int ProFileType::flagsExt()
{
    return _flagsExt;
}

}
