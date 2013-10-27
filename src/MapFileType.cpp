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
#include "../src/DatFileEntry.h"
#include "../src/MapElevation.h"
#include "../src/MapObject.h"
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
    delete _elevations;
}

void MapFileType::_initialize()
{
    if (_initialized) return;
    if (_proFileTypeLoaderCallback == 0) throw Exception("MapFileType::_initialize() - proto loader callback not defined");
    DatFileItem::_initialize();
    DatFileItem::setPosition(0);

    _elevations = new std::vector<MapElevation *>;

    *this >> _version;

    char buffer[17] = {0};
    this->readBytes(buffer, 16);
    _name += buffer;

    *this >> _defaultPosition >> _defaultElevation >> _defaultOrientaion
          >> _localVarsNumber >> _scriptId >> _elevationsFlag;


    unsigned int elevations = 0;
    if ((_elevationsFlag & 2) == 0) elevations++;
    if ((_elevationsFlag & 4) == 0) elevations++;
    if ((_elevationsFlag & 8) == 0) elevations++;

    *this >> _unknown1 >> _globalVarsNumber >> _mapId >> _timeTicks;

    this->skipBytes(4*44); // unkonwn

    // GLOBAL AND LOCAL VARS SECTION

    this->skipBytes(4*_globalVarsNumber); // global variables

    this->skipBytes(4*_localVarsNumber); // local variables

    // TILES SECTION
    for (unsigned int i = 0; i < elevations; i++)
    {
        _elevations->push_back(new MapElevation);

        for (unsigned int i = 0; i < 10000; i++)
        {
            *this >> _elevations->back()->roofTiles()->at(i);
            *this >> _elevations->back()->floorTiles()->at(i);
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
                    unsigned int PID;
                    *this >> PID;
                    switch ((PID & 0xFF000000) >> 24)
                    {
                        case 1:
                            this->skipBytes(17*4);
                            break;
                        case 2:
                            this->skipBytes(16*4);
                            break;
                        default:
                            this->skipBytes(15*4);
                            break;
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
                 break;
             }
        }
    }

    //OBJECTS
    int objectsTotal;
    *this >> objectsTotal;

    for (unsigned int i = 0; i != elevations; ++i)
    {
        unsigned int objectsOnElevation;
        *this >> objectsOnElevation;
        for (unsigned int j = 0; j != objectsOnElevation; ++j)
        {
            MapObject * object = _readObject();
            _elevations->at(i)->objects()->push_back(object);

            if (object->objectId() == 0) throw 999;

            if (object->inventorySize() > 0)
            {

                if (object->inventorySize() > objectsOnElevation) throw 777;

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
    unsigned int SID;
    *this >> SID;
    object->setScriptTypeId(SID >> 24);
    object->setScriptId( 0x00FFFFFF & SID);
    *this >> int32;
    object->setMapScriptId( int32 );
    *this >> uint32;
    object->setInventorySize( uint32 );
    *this >> uint32;
    object->setUnknown11( uint32 );
    *this >> uint32;
    object->setUnknown12( uint32 );
    *this >> uint32;
    object->setUnknown13( uint32 );

    //ProFileType * pr ;
    ProFileTypeLoaderCallback protoCallback = callback();

    switch (object->objectTypeId())
    {
        case ProFileType::TYPE_ITEM:
            object->setObjectSubtypeId(protoCallback(PID)->objectSubtypeId());
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
                    break;
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
            object->setObjectSubtypeId(protoCallback(PID)->objectSubtypeId());
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
                    throw ":(";
                    break;
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
            break;
    }
    return object;
}

std::vector<MapElevation *> * MapFileType::elevations()
{
    _initialize();
    return _elevations;
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

}
