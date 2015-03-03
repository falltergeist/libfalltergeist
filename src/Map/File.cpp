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
#include <algorithm>
#include <iostream>

// libfalltergeist includes
#include "../Exception.h"
#include "../Map/File.h"
#include "../Map/Elevation.h"
#include "../Map/Object.h"
#include "../Map/Script.h"
#include "../Pro/File.h"

// Third party includes

namespace libfalltergeist
{
namespace Map
{

File::File(Dat::Entry* datFileEntry) : Dat::Item(datFileEntry)
{
}

File::File(std::ifstream * stream) : Dat::Item(stream)
{
}

File::~File()
{
    for (auto elevation : _elevations)
    {
        delete elevation;
    }

    for (auto script : _scripts)
    {
        delete script;
    }
}

void File::_initialize()
{
    if (_initialized) return;
    if (_proFileTypeLoaderCallback == 0) throw Exception("File::_initialize() - proto loader callback not defined");
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    _version = uint32();

    char name[16];
    this->readBytes(name, 16);
    _name = name;
    std::transform(_name.begin(),_name.end(),_name.begin(), ::tolower);

    _defaultPosition   = uint32();
    _defaultElevation  = uint32();
    _defaultOrientaion = uint32();
    _LVARsize          = uint32();
    _scriptId          = int32();
    _elevationFlags    = uint32();

    unsigned elevations = 0;
    if ((_elevationFlags & 2) == 0) elevations++;
    if ((_elevationFlags & 4) == 0) elevations++;
    if ((_elevationFlags & 8) == 0) elevations++;

    _unknown1       = int32();
    _MVARsize       = uint32();
    _mapId          = uint32();
    _timeSinceEpoch = uint32();

    this->skipBytes(4*44); // unkonwn

    // MVAR AND SVAR SECTION
    for (unsigned int i = 0; i != _MVARsize; ++i)
    {
        _MVARS.push_back(int32());
    }

    for (unsigned int i = 0; i != _LVARsize; ++i)
    {
        _LVARS.push_back(int32());
    }

    // TILES SECTION
    for (unsigned int i = 0; i < elevations; i++)
    {
        _elevations.push_back(new Elevation);

        for (unsigned i = 0; i < 10000; i++)
        {
            _elevations.back()->roofTiles()->push_back(uint16());
            _elevations.back()->floorTiles()->push_back(uint16());
        }
    }

    // SCRIPTS SECTION
    for (unsigned i = 0; i < 5; i++)
    {
        uint32_t count = uint32();
        if (count > 0)
        {
            uint32_t loop = count;
            if (count%16 > 0 )
            {
                loop += 16 - count%16;
            }

            uint32_t check = 0;
            for (unsigned j = 0; j < loop; j++)
            {

                auto script = new Script();
                script->setPID(int32());

                uint32(); // unknown1

                switch ((script->PID() & 0xFF000000) >> 24)
                {
                    case 1:
                        uint32(); //unknown 2
                        uint32(); //unknown 3
                        break;
                    case 2:
                        uint32(); //unknown 2
                        break;
                    default:
                        break;
                }
                uint32(); //unknown 4
                script->setScriptId(int32());
                uint32(); //unknown 5
                uint32(); //unknown 6
                uint32(); //unknown 7
                uint32(); //unknown 8
                uint32(); //unknown 9
                uint32(); //unknown 10
                uint32(); //unknown 11
                uint32(); //unknown 12
                uint32(); //unknown 13
                uint32(); //unknown 14
                uint32(); //unknown 15
                uint32(); //unknown 16

                if (j < count)
                {
                    _scripts.push_back(script);
                }
                else
                {
                    delete script;
                }

                if ((j % 16) == 15)
                {
                    check += uint32();
                    uint32();
                }
            }
            if (check != count)
            {
                throw Exception("File::open() - rror reading scripts: check is incorrect");
            }
        }
    }

    //OBJECTS SECTION
    uint32(); // objects total
    for (unsigned i = 0; i != elevations; ++i)
    {
        unsigned objectsOnElevation = uint32();
        for (unsigned j = 0; j != objectsOnElevation; ++j)
        {
            auto object = _readObject();
            _elevations.at(i)->objects()->push_back(object);

            if (object->inventorySize() > 0)
            {
                for (unsigned int i = 0; i != object->inventorySize(); ++i)
                {
                    uint32_t ammount = uint32();
                    auto subobject = _readObject();
                    subobject->setAmmount(ammount);
                    object->children()->push_back(subobject);
                }
            }
        }
    }
}

Object* File::_readObject()
{
    auto object =new Object();

    object->setUnknown1(uint32());
    object->setHexPosition(int32());
    object->setUnknown2(uint32());
    object->setUnknown3(uint32());
    object->setUnknown4(uint32());
    object->setUnknown5(uint32());
    object->setFrameNumber(uint32());
    object->setOrientation(uint32());
    uint32_t FID = uint32();
    object->setFrmTypeId(FID >> 24);
    object->setFrmId(0x00FFFFFF & FID);
    object->setUnknown6(uint32());
    object->setElevation(uint32());
    uint32_t PID = uint32();
    object->setObjectTypeId(PID >> 24);
    object->setObjectId(0x00FFFFFF & PID);
    object->setUnknown7(uint32());
    object->setUnknown8(uint32());
    object->setUnknown9(uint32());
    object->setUnknown10(uint32());

    int32_t SID = int32();
    if (SID != -1)
    {
        for (auto it = _scripts.begin(); it != _scripts.end(); ++it)
        {
            if ((*it)->PID() == SID)
            {
                object->setMapScriptId((*it)->scriptId());
            }
        }
    }

    SID = int32();
    if (SID != -1)
    {
        object->setScriptId(SID);
    }

    object->setInventorySize(uint32());
    object->setUnknown11(uint32());
    object->setUnknown12(uint32());
    object->setUnknown13(uint32());

    switch (object->objectTypeId())
    {
        case Pro::TYPE_ITEM:
            object->setObjectSubtypeId(callback()(PID)->subtypeId());
            switch(object->objectSubtypeId())
            {
                case Pro::TYPE_ITEM_AMMO:
                    uint32();
                    break;
                case Pro::TYPE_ITEM_KEY:
                    uint32();
                    break;
                case Pro::TYPE_ITEM_MISC:
                    uint32();
                    break;
                case Pro::TYPE_ITEM_WEAPON:
                    uint32();
                    uint32();
                    break;
                case Pro::TYPE_ITEM_ARMOR:
                    break;
                case Pro::TYPE_ITEM_CONTAINER:
                    break;
                case Pro::TYPE_ITEM_DRUG:
                    break;
                default:
                    throw Exception("File::_readObject() - unknown item type");
            }
            break;
        case Pro::TYPE_CRITTER:
            uint32();
            uint32();
            uint32();
            uint32();
            uint32();
            uint32();
            uint32();
            uint32();
            uint32();
            uint32();
            object->setFrmId(FID & 0x00000FFF);
            object->setObjectID1((FID & 0x0000F000) >> 12);
            object->setObjectID2((FID & 0x00FF0000) >> 16);
            object->setFrmTypeId((FID & 0x0F000000) >> 24);
            object->setObjectID3((FID & 0xF0000000) >> 28);
            break;
        case Pro::TYPE_SCENERY:
            object->setObjectSubtypeId(callback()(PID)->subtypeId());
            switch(object->objectSubtypeId())
            {
                case Pro::TYPE_SCENERY_LADDER_TOP:
                case Pro::TYPE_SCENERY_LADDER_BOTTOM:
                    uint32();
                    uint32();
                    break;
                case Pro::TYPE_SCENERY_STAIRS:
                    uint32();
                    uint32();
                    break;
                case Pro::TYPE_SCENERY_ELEVATOR:
                    uint32();
                    uint32();
                    break;
                case Pro::TYPE_SCENERY_DOOR:
                    uint32();
                    break;
                case Pro::TYPE_SCENERY_GENERIC:
                    break;
                default:
                    throw Exception("File::_readObject() - unknown scenery type");
            }
            break;
        case Pro::TYPE_WALL:
            break;
        case Pro::TYPE_TILE:
            break;
        case Pro::TYPE_MISC:
            switch(object->objectId())
            {
                case 12:
                    break;
                // Exit Grids
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    object->setExitMap(int32());
                    object->setExitPosition(int32());
                    object->setExitElevation(int32());
                    object->setExitOrientation(int32());
                    break;
                default:
                    uint32();
                    uint32();
                    uint32();
                    uint32();
                    break;
            }
            break;
        default:
            throw Exception("File::_readObject() - unknown type");
    }
    return object;
}

std::vector<Elevation*>* File::elevations()
{
    return &_elevations;
}

File* File::setCallback(ProFileTypeLoaderCallback callback)
{    
    _proFileTypeLoaderCallback = callback;
    _initialize();
    return this;
}

ProFileTypeLoaderCallback File::callback() const
{
    return _proFileTypeLoaderCallback;
}

unsigned int File::version() const
{
    return _version;
}

unsigned int File::defaultPosition() const
{
    return _defaultPosition;
}

unsigned int File::defaultElevation() const
{
    return _defaultElevation;
}

unsigned int File::defaultOrientation() const
{
    return _defaultOrientaion;
}

int File::scriptId() const
{
    return _scriptId;
}

std::string File::name() const
{
    return _name;
}

unsigned int File::elevationFlags() const
{
    return _elevationFlags;
}

int File::unknown1() const
{
    return _unknown1;
}

unsigned int File::mapId() const
{
    return _mapId;
}

unsigned int File::timeSinceEpoch() const
{
    return _timeSinceEpoch;
}

std::vector<int>* File::LVARS()
{
    return &_LVARS;
}

std::vector<int>* File::MVARS()
{
    return &_MVARS;
}

std::vector<Script*>* File::scripts()
{
    return &_scripts;
}

}
}
