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
#include <iostream>

// libfalltergeist includes
#include "../src/MapFileType.h"
#include "../src/MapElevation.h"
#include "../src/MapObject.h"
#include "../src/MapScript.h"
#include "../src/ProFileType.h"
#include "../src/Exception.h"

// Third party includes

namespace libfalltergeist
{

MapFileType::MapFileType(DatFileEntry * datFileEntry) : DatFileItem(datFileEntry)
{
}

MapFileType::MapFileType(std::ifstream * stream) : DatFileItem(stream)
{
}

MapFileType::~MapFileType()
{
}

void MapFileType::_initialize()
{
    if (_initialized) return;
    if (_proFileTypeLoaderCallback == 0) throw Exception("MapFileType::_initialize() - proto loader callback not defined");
    DatFileItem::_initialize();
    DatFileItem::setPosition(0);

    *this >> _version;

    char buffer[17] = {0};
    this->readBytes(buffer, 16);
    _name += buffer;

    *this >> _defaultPosition >> _defaultElevation >> _defaultOrientaion
          >> _SVARNumber >> _scriptId >> _elevationsFlag;


    unsigned int elevations = 0;
    if ((_elevationsFlag & 2) == 0) elevations++;
    if ((_elevationsFlag & 4) == 0) elevations++;
    if ((_elevationsFlag & 8) == 0) elevations++;

    *this >> _unknown1 >> _MVARNumber >> _mapId >> _timeTicks;

    this->skipBytes(4*44); // unkonwn

    // MVAR AND SVAR SECTION
    std::cout << "MVARS: " << std::dec << _MVARNumber << std::endl;
    for (unsigned int i = 0; i != _MVARNumber; ++i)
    {
        unsigned int value;
        *this >> value;
        std::cout << "MVAR" << std::dec << i << " 0x" << std::hex << value << std::endl;
    }

    std::cout << "SVARS: " << std::dec << _SVARNumber << std::endl;
    for (unsigned int i = 0; i != _SVARNumber; ++i)
    {
        unsigned int value;
        *this >> value;
        std::cout << "SVAR" << std::dec << i << " 0x" << std::hex << value << std::endl;
    }


    // TILES SECTION
    for (unsigned int i = 0; i < elevations; i++)
    {
        _elevations.push_back(new MapElevation);

        for (unsigned int i = 0; i < 10000; i++)
        {
            unsigned short roof, floor;
            *this >> roof >> floor;
            _elevations.back()->roofTiles()->push_back(roof);
            _elevations.back()->floorTiles()->push_back(floor);
        }
    }
    // SCRIPTS SECTION
    for (unsigned int i = 0; i < 5; i++)
    {
        unsigned int count;        
        *this >> count;
        if (count > 0)
        {
            short loop = count;
            if (count%16 > 0 ) loop += 16 - count%16;

            unsigned int check = 0;
            for (unsigned short j = 0; j < loop; j++)
            {
                {
                    int PID;
                    *this >> PID;

                    auto script = new MapScript(PID);
                    this->skipBytes(4); // unknown1

                    switch ((PID & 0xFF000000) >> 24)
                    {
                        case 1:
                            this->skipBytes(4); //unknown 2
                            this->skipBytes(4); //unknown 3
                            break;
                        case 2:
                            this->skipBytes(4); //unknown 2
                            break;
                        default:
                            break;
                    }
                    this->skipBytes(4); //unknown 4
                    int scriptId;
                    *this >> scriptId;
                    script->setScriptId(scriptId);
                    this->skipBytes(4); //unknown 5
                    this->skipBytes(4); //unknown 6
                    this->skipBytes(4); //unknown 7
                    this->skipBytes(4); //unknown 8
                    this->skipBytes(4); //unknown 9
                    this->skipBytes(4); //unknown 10
                    this->skipBytes(4); //unknown 11
                    this->skipBytes(4); //unknown 12
                    this->skipBytes(4); //unknown 13
                    this->skipBytes(4); //unknown 14
                    this->skipBytes(4); //unknown 15
                    this->skipBytes(4); //unknown 16

                    if (j < count)
                    {
                        std::cout << "Map script: 0x" << std::hex << script->PID() << std::endl;
                        _scripts.push_back(script);
                    }
                    else
                    {
                        delete script;
                    }

                }
                if ((j % 16) == 15)
                {
                    unsigned int v;
                    *this >> v;
                    check += v;

                    this->skipBytes(4);
                }
             }
             if (check != count)
             {
                 throw Exception("MapFileType::open() - rror reading scripts: check is incorrect");
             }
        }
    }

    //OBJECTS SECTION
    int objectsTotal;
    *this >> objectsTotal;

    for (unsigned int i = 0; i != elevations; ++i)
    {
        unsigned int objectsOnElevation;
        *this >> objectsOnElevation;
        for (unsigned int j = 0; j != objectsOnElevation; ++j)
        {
            MapObject * object = _readObject();
            _elevations.at(i)->objects()->push_back(object);

            if (object->inventorySize() > 0)
            {
                for (unsigned int i = 0; i != object->inventorySize(); ++i)
                {
                    this->skipBytes(4);  // items count ?
                    MapObject * subobject = _readObject();
                    object->children()->push_back(subobject);
                }
            }
        }
    }
}

MapObject * MapFileType::_readObject()
{
    MapObject * object = new MapObject();

    unsigned int uint32;
    int int32;

    *this >> uint32;
    object->setUnknown1( uint32 );
    *this >> int32;
    object->setHexPosition( int32 );
    *this >> uint32;
    object->setUnknown2( uint32 );
    *this >> uint32;
    object->setUnknown3( uint32 );
    *this >> uint32;
    object->setUnknown4( uint32 );
    *this >> uint32;
    object->setUnknown5( uint32 );
    *this >> uint32;
    object->setFrameNumber( uint32 );
    *this >> uint32;
    object->setOrientation( uint32 );
    unsigned int FID;
    *this >> FID;
    object->setFrmTypeId( FID >> 24 );
    object->setFrmId( 0x00FFFFFF & FID );
    *this >> uint32;
    object->setUnknown6( uint32 );
    *this >> uint32;
    object->setElevation( uint32 );
    unsigned int PID;
    *this >> PID;

    object->setObjectTypeId( PID >> 24 );
    object->setObjectId( 0x00FFFFFF & PID);
    *this >> uint32;
    object->setUnknown7( uint32 );
    *this >> uint32;
    object->setUnknown8( uint32 );
    *this >> uint32;
    object->setUnknown9( uint32 );
    *this >> uint32;
    object->setUnknown10( uint32 );
    *this >> int32;
    if (int32 != -1)
    {
        for (auto it = _scripts.begin(); it != _scripts.end(); ++it)
        {
            if ((*it)->PID() == int32)
            {
                std::cout << "Map script: " <<  std::dec << (*it)->scriptId() << std::endl;
                object->setMapScriptId((*it)->scriptId());
            }
        }
    }

    *this >> int32;
    if (int32 != -1)
    {
        std::cout << "SID: " << std::dec <<  int32 << std::endl;
        object->setScriptId(int32);
    }
    if (PID == 0x01000003)
    {
        std::cout << "!!! " << int32 << std::endl;
    }
    *this >> uint32;
    object->setInventorySize( uint32 );
    *this >> uint32;
    object->setUnknown11( uint32 );
    *this >> uint32;
    object->setUnknown12( uint32 );
    *this >> uint32;
    object->setUnknown13( uint32 );

    switch (object->objectTypeId())
    {
        case ProFileType::TYPE_ITEM:
            object->setObjectSubtypeId(callback()(PID)->objectSubtypeId());
            switch(object->objectSubtypeId())
            {
                case ProFileType::TYPE_ITEM_AMMO:
                    this->skipBytes(4);
                    break;
                case ProFileType::TYPE_ITEM_KEY:
                    this->skipBytes(4);
                    break;
                case ProFileType::TYPE_ITEM_MISC:
                    this->skipBytes(4);
                    break;
                case ProFileType::TYPE_ITEM_WEAPON:
                    this->skipBytes(4*2);
                    break;
                case ProFileType::TYPE_ITEM_ARMOR:
                    break;
                case ProFileType::TYPE_ITEM_CONTAINER:
                    break;
                case ProFileType::TYPE_ITEM_DRUG:
                    break;
                default:
                    throw Exception("MapFileType::_readObject() - unknown item type");
            }
            break;
        case ProFileType::TYPE_CRITTER:
            this->skipBytes(10*4);

            object->setFrmId(FID & 0x00000FFF);
            object->setObjectID1((FID & 0x0000F000) >> 12);
            object->setObjectID2((FID & 0x00FF0000) >> 16);
            object->setFrmTypeId((FID & 0x0F000000) >> 24);
            object->setObjectID3((FID & 0xF0000000) >> 28);
            break;
        case ProFileType::TYPE_SCENERY:
            object->setObjectSubtypeId(callback()(PID)->objectSubtypeId());
            switch(object->objectSubtypeId())
            {
                case ProFileType::TYPE_SCENERY_LADDER_TOP:
                case ProFileType::TYPE_SCENERY_LADDER_BOTTOM:
                    this->skipBytes(4*2);
                    break;
                case ProFileType::TYPE_SCENERY_STAIR:
                    this->skipBytes(4*2);
                    break;
                case ProFileType::TYPE_SCENERY_ELEVATOR:
                    this->skipBytes(4*2);
                    break;
                case ProFileType::TYPE_SCENERY_DOOR:
                    this->skipBytes(4*1);
                    break;
                case ProFileType::TYPE_SCENERY_GENERIC:
                    break;
                default:
                    throw Exception("MapFileType::_readObject() - unknown scenery type");
            }
            break;
        case ProFileType::TYPE_WALL:
            break;
        case ProFileType::TYPE_TILE:
            break;
        case ProFileType::TYPE_MISC:
            switch(object->objectId())
            {
                case 0xC:
                    break;
                default:
                    this->skipBytes(4*4);
                    break;
            }
            break;
        default:
            throw Exception("MapFileType::_readObject() - unknown type");
    }
    return object;
}

std::vector<MapElevation*>* MapFileType::elevations()
{
    _initialize();
    return &_elevations;
}

MapFileType* MapFileType::setCallback(ProFileTypeLoaderCallback callback)
{
    _proFileTypeLoaderCallback = callback;
    return this;
}

ProFileTypeLoaderCallback MapFileType::callback()
{
    return _proFileTypeLoaderCallback;
}

unsigned int MapFileType::defaultPosition()
{
    _initialize();
    return _defaultPosition;
}

unsigned int MapFileType::defaultElevation()
{
    _initialize();
    return _defaultElevation;
}

unsigned int MapFileType::defaultOrientation()
{
    _initialize();
    return _defaultOrientaion;
}

int MapFileType::scriptId()
{
    return _scriptId;
}

}
