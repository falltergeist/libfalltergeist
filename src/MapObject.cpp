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

// C++ standard includes

// libfalltergeist includes
#include "../src/MapObject.h"

// Third party includes

namespace libfalltergeist
{

MapObject::MapObject()
{
    _objectSubtypeId = 0;
}

MapObject::~MapObject()
{
}

std::vector<std::shared_ptr<MapObject>>* MapObject::children()
{
    return &_children;
}

unsigned int MapObject::unknown1()
{
    return _unknown1;
}

void MapObject::setUnknown1(unsigned int value)
{
    _unknown1 = value;
}

int MapObject::hexPosition()
{
    return _hexPosition;
}

void MapObject::setHexPosition(int value)
{
    _hexPosition = value;
}

unsigned int MapObject::unknown2()
{
    return _unknown2;
}

void MapObject::setUnknown2(unsigned int value)
{
    _unknown2 = value;
}

unsigned int MapObject::unknown3()
{
    return _unknown3;
}

void MapObject::setUnknown3(unsigned int value)
{
    _unknown3 = value;
}

unsigned int MapObject::unknown4()
{
    return _unknown4;
}

void MapObject::setUnknown4(unsigned int value)
{
    _unknown4 = value;
}

unsigned int MapObject::frameNumber()
{
    return _frameNumber;
}

void MapObject::setFrameNumber(unsigned int value)
{
    _frameNumber = value;
}

unsigned int MapObject::orientation()
{
    return _orientation;
}

void MapObject::setOrientation(unsigned int value)
{
    _orientation = value;
}

unsigned int MapObject::FID()
{
    return (_frmTypeId << 24) | _frmId;
}

unsigned int MapObject::frmTypeId()
{
    return _frmTypeId;
}

void MapObject::setFrmTypeId(unsigned int value)
{
    _frmTypeId = value;
}

unsigned int MapObject::frmId()
{
    return _frmId;
}

void MapObject::setFrmId(unsigned int value)
{
    _frmId = value;
}

unsigned int MapObject::unknown5()
{
    return _unknown5;
}

void MapObject::setUnknown5(unsigned int value)
{
    _unknown5 = value;
}

unsigned int MapObject::elevation()
{
    return _elevation;
}

void MapObject::setElevation(unsigned int value)
{
    _elevation = value;
}

unsigned int MapObject::PID()
{
    return (_objectID3 << 28) |(_objectTypeId << 24) | (_objectID2 << 16) | (_objectID1 << 12) | _objectId;
}

unsigned int MapObject::objectTypeId()
{
    return _objectTypeId;
}

void MapObject::setObjectTypeId(unsigned int value)
{
    _objectTypeId = value;
}

unsigned int MapObject::objectId()
{
    return _objectId;
}

void MapObject::setObjectId(unsigned int value)
{
    _objectId = value;
}

unsigned int MapObject::objectID1()
{
    return _objectID1;
}

void MapObject::setObjectID1(unsigned int value)
{
    _objectID1 = value;
}

unsigned int MapObject::objectID2()
{
    return _objectID2;
}

void MapObject::setObjectID2(unsigned int value)
{
    _objectID2 = value;
}

unsigned int MapObject::objectID3()
{
    return _objectID3;
}

void MapObject::setObjectID3(unsigned int value)
{
    _objectID3 = value;
}

unsigned int MapObject::objectSubtypeId()
{
    return _objectSubtypeId;
}

void MapObject::setObjectSubtypeId(unsigned int value)
{
    _objectSubtypeId = value;
}

unsigned int MapObject::unknown6()
{
    return _unknown6;
}

void MapObject::setUnknown6(unsigned int value)
{
    _unknown6 = value;
}

unsigned int MapObject::unknown7()
{
    return _unknown7;
}

void MapObject::setUnknown7(unsigned int value)
{
    _unknown7 = value;
}

unsigned int MapObject::unknown8()
{
    return _unknown8;
}

void MapObject::setUnknown8(unsigned int value)
{
    _unknown8 = value;
}

unsigned int MapObject::unknown9()
{
    return _unknown9;
}

void MapObject::setUnknown9(unsigned int value)
{
    _unknown9 = value;
}

int MapObject::scriptId()
{
    return _scriptId;
}

void MapObject::setScriptId(int value)
{
    _scriptId = value;
}

int MapObject::mapScriptId()
{
    return _mapScriptId;
}

void MapObject::setMapScriptId(int value)
{
    _mapScriptId = value;
}

unsigned int MapObject::unknown10()
{
    return _unknown10;
}

void MapObject::setUnknown10(unsigned int value)
{
    _unknown10 = value;
}

unsigned int MapObject::inventorySize()
{
    return _inventorySize;
}

void MapObject::setInventorySize(unsigned int value)
{
    _inventorySize = value;
}

unsigned int MapObject::unknown11()
{
    return _unknown11;
}

void MapObject::setUnknown11(unsigned int value)
{
    _unknown11 = value;
}

unsigned int MapObject::unknown12()
{
    return _unknown12;
}

void MapObject::setUnknown12(unsigned int value)
{
    _unknown12 = value;
}

unsigned int MapObject::unknown13()
{
    return _unknown13;
}

void MapObject::setUnknown13(unsigned int value)
{
    _unknown13 = value;
}

int MapObject::exitMap()
{
    return _exitMap;
}

void MapObject::setExitMap(int value)
{
    _exitMap = value;
}

int MapObject::exitPosition()
{
    return _exitPosition;
}

void MapObject::setExitPosition(int value)
{
    _exitPosition = value;
}

int MapObject::exitElevation()
{
    return _exitElevation;
}

void MapObject::setExitElevation(int value)
{
    _exitElevation = value;
}

int MapObject::exitOrientation()
{
    return _exitOrientation;
}

void MapObject::setExitOrientation(int value)
{
    _exitOrientation = value;
}

unsigned int MapObject::ammount()
{
    return _ammount;
}

void MapObject::setAmmount(unsigned int value)
{
    _ammount = value;
}

}
