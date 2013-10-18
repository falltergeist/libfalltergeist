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
    datFileItem()->setPosition(0);

    unsigned int PID = datFileItem()->readUint32();

    _objectTypeId = (PID & 0x0F000000) >> 28;
    _objectId = PID & 0x00000FFF;


    _messageId = datFileItem()->readUint32();


    unsigned int FID = datFileItem()->readUint32();

    _frmTypeId = (FID & 0x0F000000) >> 28;
    _frmOffset = (FID & 0x00FF0000) >> 16;

    _frmId = FID & 0x0000FFFF;


    switch (_objectTypeId)
    {
        case TYPE_ITEM:
            _lightDistance = datFileItem()->readUint32();
            _lightIntencity = datFileItem()->readUint32();

            _flags = datFileItem()->readUint32();
            _flagsExt = datFileItem()->readUint32();

            _scriptTypeId = datFileItem()->readUint8();
            datFileItem()->skipBytes(1);
            _scriptId = datFileItem()->readUint16();

            _objectSubtypeId = datFileItem()->readUint32();

            _materialId = datFileItem()->readUint32();
            _containerSize = datFileItem()->readUint32();

            _weight = datFileItem()->readUint32();
            _basePrice = datFileItem()->readUint32();

            _inventoryFrmTypeId = datFileItem()->readUint8();
            datFileItem()->skipBytes(1);
            _inventoryFrmTypeId = datFileItem()->readUint16();

            _soundId = datFileItem()->readUint8();

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
        case TYPE_CRITTER:
            _lightDistance = datFileItem()->readUint32();
            _lightIntencity = datFileItem()->readUint32();

            _flags = datFileItem()->readUint32();
            _flagsExt = datFileItem()->readUint32();

            _scriptTypeId = datFileItem()->readUint8();
            datFileItem()->skipBytes(1);
            _scriptId = datFileItem()->readUint16();

            _headFrmTypeId = datFileItem()->readUint8();
            datFileItem()->skipBytes(1);
            _headFrmId = datFileItem()->readUint16();


            // more ...

            break;
        case TYPE_SCENERY:
            _lightDistance = datFileItem()->readUint32();
            _lightIntencity = datFileItem()->readUint32();

            _flags = datFileItem()->readUint32();
            _flagsExt = datFileItem()->readUint32();

            _scriptTypeId = datFileItem()->readUint8();
            datFileItem()->skipBytes(1);
            _scriptId = datFileItem()->readUint16();

            _objectSubtypeId = datFileItem()->readUint32();

            _materialId = datFileItem()->readUint32();

            _soundId = datFileItem()->readUint8();

            break;
        case TYPE_WALL:
            _lightDistance = datFileItem()->readUint32();
            _lightIntencity = datFileItem()->readUint32();

            _flags = datFileItem()->readUint32();
            _flagsExt = datFileItem()->readUint32();

            _scriptTypeId = datFileItem()->readUint8();
            datFileItem()->skipBytes(1);
            _scriptId = datFileItem()->readUint16();

            _materialId = datFileItem()->readUint32();
            break;
        case TYPE_TILE:
            _flags = datFileItem()->readUint32();
            _flagsExt = datFileItem()->readUint32();

            datFileItem()->skipBytes(4); //unknown

            _materialId = datFileItem()->readUint32();
            break;
        case TYPE_MISC:
            _lightDistance = datFileItem()->readUint32();
            _lightIntencity = datFileItem()->readUint32();

            _flags = datFileItem()->readUint32();
            _flagsExt = datFileItem()->readUint32();
            break;
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
