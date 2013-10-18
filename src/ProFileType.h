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

#ifndef LIBFALLTERGEIST_PROFILETYPE_H
#define LIBFALLTERGEIST_PROFILETYPE_H

// C++ standard includes

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
class DatFileItem;

class ProFileType
{
protected:
    DatFileItem * _datFileItem;

    unsigned int _objectTypeId;
    unsigned int _objectSubtypeId;
    unsigned int _objectId;

    unsigned int _messageId;

    unsigned int _frmTypeId;
             int _frmOffset;
    unsigned int _frmId;

    unsigned int _headFrmTypeId;
    unsigned int _headFrmId;

    unsigned int _lightDistance;
    unsigned int _lightIntencity;

    unsigned int _flags;
    unsigned int _flagsExt;

    unsigned int _scriptTypeId;
    unsigned int _scriptId;

    unsigned int _materialId;
    unsigned int _containerSize;
    unsigned int _weight;
    unsigned int _basePrice;

    unsigned int _inventoryFrmTypeId;
    unsigned int _inventoryFrmId;

    unsigned int _soundId;


public:
    enum { TYPE_ITEM = 0, TYPE_CRITTER, TYPE_SCENERY, TYPE_WALL, TYPE_TILE, TYPE_MISC };
    enum { TYPE_ITEM_ARMOR = 0, TYPE_ITEM_CONTAINER, TYPE_ITEM_DRUG, TYPE_ITEM_WEAPON, TYPE_ITEM_AMMO, TYPE_ITEM_MISC, TYPE_ITEM_KEY };
    enum { TYPE_SCENERY_DOOR = 0, TYPE_SCENERY_STAIR, TYPE_SCENERY_ELEVATOR, TYPE_SCENERY_LADDER_BOTTOM, TYPE_SCENERY_LADDER_TOP, TYPE_SCENERY_GENERIC };

    ProFileType(DatFileItem * datFileItem);
    ~ProFileType();

    DatFileItem * datFileItem();

    void open();

    unsigned int objectTypeId();
    unsigned int objectSubtypeId();
    unsigned int messageId();
    int frmOffset();
    unsigned int flagsExt();

};
}

#endif // LIBFALLTERGEIST_PROFILETYPE_H
