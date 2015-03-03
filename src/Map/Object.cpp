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
#include "../Map/Object.h"

// Third party includes

namespace libfalltergeist
{
namespace Map
{

Object::Object()
{
}

Object::~Object()
{
    for (auto child : _children)
    {
        delete child;
    }
}

std::vector<Object*>* Object::children()
{
    return &_children;
}

unsigned int Object::unknown1()
{
    return _unknown1;
}

void Object::setUnknown1(unsigned int value)
{
    _unknown1 = value;
}

int Object::hexPosition()
{
    return _hexPosition;
}

void Object::setHexPosition(int value)
{
    _hexPosition = value;
}

unsigned int Object::unknown2()
{
    return _unknown2;
}

void Object::setUnknown2(unsigned int value)
{
    _unknown2 = value;
}

unsigned int Object::unknown3()
{
    return _unknown3;
}

void Object::setUnknown3(unsigned int value)
{
    _unknown3 = value;
}

unsigned int Object::unknown4()
{
    return _unknown4;
}

void Object::setUnknown4(unsigned int value)
{
    _unknown4 = value;
}

unsigned int Object::frameNumber()
{
    return _frameNumber;
}

void Object::setFrameNumber(unsigned int value)
{
    _frameNumber = value;
}

unsigned int Object::orientation()
{
    return _orientation;
}

void Object::setOrientation(unsigned int value)
{
    _orientation = value;
}

unsigned int Object::FID()
{
    return (_frmTypeId << 24) | _frmId;
}

unsigned int Object::frmTypeId()
{
    return _frmTypeId;
}

void Object::setFrmTypeId(unsigned int value)
{
    _frmTypeId = value;
}

unsigned int Object::frmId()
{
    return _frmId;
}

void Object::setFrmId(unsigned int value)
{
    _frmId = value;
}

unsigned int Object::unknown5()
{
    return _unknown5;
}

void Object::setUnknown5(unsigned int value)
{
    _unknown5 = value;
}

unsigned int Object::elevation()
{
    return _elevation;
}

void Object::setElevation(unsigned int value)
{
    _elevation = value;
}

unsigned int Object::PID()
{
    return (_objectID3 << 28) |(_objectTypeId << 24) | (_objectID2 << 16) | (_objectID1 << 12) | _objectId;
}

unsigned int Object::objectTypeId()
{
    return _objectTypeId;
}

void Object::setObjectTypeId(unsigned int value)
{
    _objectTypeId = value;
}

unsigned int Object::objectId()
{
    return _objectId;
}

void Object::setObjectId(unsigned int value)
{
    _objectId = value;
}

unsigned int Object::objectID1()
{
    return _objectID1;
}

void Object::setObjectID1(unsigned int value)
{
    _objectID1 = value;
}

unsigned int Object::objectID2()
{
    return _objectID2;
}

void Object::setObjectID2(unsigned int value)
{
    _objectID2 = value;
}

unsigned int Object::objectID3()
{
    return _objectID3;
}

void Object::setObjectID3(unsigned int value)
{
    _objectID3 = value;
}

unsigned int Object::objectSubtypeId()
{
    return _objectSubtypeId;
}

void Object::setObjectSubtypeId(unsigned int value)
{
    _objectSubtypeId = value;
}

unsigned int Object::unknown6()
{
    return _unknown6;
}

void Object::setUnknown6(unsigned int value)
{
    _unknown6 = value;
}

unsigned int Object::unknown7()
{
    return _unknown7;
}

void Object::setUnknown7(unsigned int value)
{
    _unknown7 = value;
}

unsigned int Object::unknown8()
{
    return _unknown8;
}

void Object::setUnknown8(unsigned int value)
{
    _unknown8 = value;
}

unsigned int Object::unknown9()
{
    return _unknown9;
}

void Object::setUnknown9(unsigned int value)
{
    _unknown9 = value;
}

int Object::scriptId()
{
    return _scriptId;
}

void Object::setScriptId(int value)
{
    _scriptId = value;
}

int Object::mapScriptId()
{
    return _mapScriptId;
}

void Object::setMapScriptId(int value)
{
    _mapScriptId = value;
}

unsigned int Object::unknown10()
{
    return _unknown10;
}

void Object::setUnknown10(unsigned int value)
{
    _unknown10 = value;
}

unsigned int Object::inventorySize()
{
    return _inventorySize;
}

void Object::setInventorySize(unsigned int value)
{
    _inventorySize = value;
}

unsigned int Object::unknown11()
{
    return _unknown11;
}

void Object::setUnknown11(unsigned int value)
{
    _unknown11 = value;
}

unsigned int Object::unknown12()
{
    return _unknown12;
}

void Object::setUnknown12(unsigned int value)
{
    _unknown12 = value;
}

unsigned int Object::unknown13()
{
    return _unknown13;
}

void Object::setUnknown13(unsigned int value)
{
    _unknown13 = value;
}

int Object::exitMap()
{
    return _exitMap;
}

void Object::setExitMap(int value)
{
    _exitMap = value;
}

int Object::exitPosition()
{
    return _exitPosition;
}

void Object::setExitPosition(int value)
{
    _exitPosition = value;
}

int Object::exitElevation()
{
    return _exitElevation;
}

void Object::setExitElevation(int value)
{
    _exitElevation = value;
}

int Object::exitOrientation()
{
    return _exitOrientation;
}

void Object::setExitOrientation(int value)
{
    _exitOrientation = value;
}

unsigned int Object::ammount()
{
    return _ammount;
}

void Object::setAmmount(unsigned int value)
{
    _ammount = value;
}

}
}
