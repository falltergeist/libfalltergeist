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
#include "../src/DatFileItem.h"
#include "../src/MapElevation.h"
#include "../src/MapObject.h"
#include "../src/ProFileType.h"
#include "../src/Exception.h"

// Third party includes

namespace libfalltergeist
{

MapFileType::MapFileType(DatFileItem * datFileItem, ProFileTypeLoaderCallback callback) : _datFileItem(datFileItem)
{
    _proFileTypeLoaderCallback = callback;
    _elevations = new std::vector<MapElevation *>;
    open();
}

MapFileType::~MapFileType()
{
    delete _elevations;
}

void MapFileType::open()
{
    DatFileItem &item = *datFileItem();

    // HEADER
    item.setPosition(0);
    item >> _version;

    char * buffer = new char[17]();
    item.readBytes(buffer, 16);
    _name += buffer;
    delete [] buffer;

    item >> _defaultPosition >> _defaultElevation >> _defaultOrientaion
         >> _localVarsNumber >> _scriptId >> _elevationsFlag;


    unsigned int elevations = 0;
    if ((_elevationsFlag & 2) == 0) elevations++;
    if ((_elevationsFlag & 4) == 0) elevations++;
    if ((_elevationsFlag & 8) == 0) elevations++;

    item >> _unknown1 >> _globalVarsNumber >> _mapId >> _timeTicks;

    item.skipBytes(4*44); // unkonwn

    // GLOBAL AND LOCAL VARS SECTION

    item.skipBytes(4*_globalVarsNumber); // global variables

    item.skipBytes(4*_localVarsNumber); // local variables

    // TILES SECTION
    for (unsigned int i = 0; i < elevations; i++)
    {
        _elevations->push_back(new MapElevation);

        for (unsigned int i = 0; i < 10000; i++)
        {
            item >> _elevations->back()->roofTiles()->at(i);
            item >> _elevations->back()->floorTiles()->at(i);
        }
    }
    // SCRIPTS SECTION
    for (unsigned int i = 0; i < 5; i++)
    {
        unsigned int count;
        item >> count;
        if (count > 0)
        {
            short loop = count;
            if (count%16 > 0 ) loop += 16 - count%16;

            int check = 0;
            for (unsigned short j = 0; j < loop; j++)
            {
                {
                    unsigned int PID;
                    item >> PID;
                    switch ((PID & 0xFF000000) >> 24)
                    {
                        case 1:
                            datFileItem()->skipBytes(17*4);
                            break;
                        case 2:
                            datFileItem()->skipBytes(16*4);
                            break;
                        default:
                            datFileItem()->skipBytes(15*4);
                            break;
                    }
                }
                if ((j % 16) == 15)
                {
                    unsigned int v;
                    item >> v;
                    check += v;

                    datFileItem()->skipBytes(4);
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
    item >> objectsTotal;

    for (unsigned int i = 0; i != elevations; ++i)
    {
        unsigned int objectsOnElevation;
        item >> objectsOnElevation;
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

                    datFileItem()->skipBytes(4);  // items count ?
                    MapObject * subobject = _readObject();

                }

            }

        }
    }

}

MapObject * MapFileType::_readObject()
{
    MapObject * object = new MapObject();

    DatFileItem& item = *datFileItem();

    unsigned int uint32;
    int int32;

    item >> uint32;
    object->setUnknown1( uint32 );
    item >> int32;
    object->setHexPosition( int32 );
    item >> uint32;
    object->setUnknown2( uint32 );
    item >> uint32;
    object->setUnknown3( uint32 );
    item >> uint32;
    object->setUnknown4( uint32 );
    item >> uint32;
    object->setUnknown5( uint32 );
    item >> uint32;
    object->setFrameNumber( uint32 );
    item >> uint32;
    object->setOrientation( uint32 );
    unsigned int FID;
    item >> FID;
    object->setFrmTypeId( FID >> 24 );
    object->setFrmId( 0x00FFFFFF & FID );
    item >> uint32;
    object->setUnknown6( uint32 );
    item >> uint32;
    object->setElevation( uint32 );
    unsigned int PID;
    item >> PID;
    object->setObjectTypeId( PID >> 24 );
    object->setObjectId( 0x00FFFFFF & PID);
    item >> uint32;
    object->setUnknown7( uint32 );
    item >> uint32;
    object->setUnknown8( uint32 );
    item >> uint32;
    object->setUnknown9( uint32 );
    item >> uint32;
    object->setUnknown10( uint32 );
    unsigned int SID;
    item >> SID;
    object->setScriptTypeId(SID >> 24);
    object->setScriptId( 0x00FFFFFF & SID);
    item >> int32;
    object->setMapScriptId( int32 );
    item >> uint32;
    object->setInventorySize( uint32 );
    item >> uint32;
    object->setUnknown11( uint32 );
    item >> uint32;
    object->setUnknown12( uint32 );
    item >> uint32;
    object->setUnknown13( uint32 );

    //ProFileType * pr ;

    switch (object->objectTypeId())
    {
        case ProFileType::TYPE_ITEM:
            object->setObjectSubtypeId(_proFileTypeLoaderCallback(PID)->objectSubtypeId());
            switch(object->objectSubtypeId())
            {
                case ProFileType::TYPE_ITEM_AMMO:
                    datFileItem()->skipBytes(4);
                    break;
                case ProFileType::TYPE_ITEM_KEY:
                    datFileItem()->skipBytes(4);
                    break;
                case ProFileType::TYPE_ITEM_MISC:
                    datFileItem()->skipBytes(4);
                    break;
                case ProFileType::TYPE_ITEM_WEAPON:
                    datFileItem()->skipBytes(4*2);
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
            datFileItem()->skipBytes(10*4);

            object->setFrmId(FID & 0x00000FFF);
            object->setObjectID1((FID & 0x0000F000) >> 12);
            object->setObjectID2((FID & 0x00FF0000) >> 16);
            object->setFrmTypeId((FID & 0x0F000000) >> 24);
            object->setObjectID3((FID & 0xF0000000) >> 28);
            break;
        case ProFileType::TYPE_SCENERY:
            object->setObjectSubtypeId(_proFileTypeLoaderCallback(PID)->objectSubtypeId());
            switch(object->objectSubtypeId())
            {
                case ProFileType::TYPE_SCENERY_LADDER_TOP:
                case ProFileType::TYPE_SCENERY_LADDER_BOTTOM:
                    datFileItem()->skipBytes(4*2);
                    break;
                case ProFileType::TYPE_SCENERY_STAIR:
                    datFileItem()->skipBytes(4*2);
                    break;
                case ProFileType::TYPE_SCENERY_ELEVATOR:
                    datFileItem()->skipBytes(4*2);
                    break;
                case ProFileType::TYPE_SCENERY_DOOR:
                    datFileItem()->skipBytes(4*1);
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
            if (object->objectId() == 0xc)
            {

            }
            else
            {
                datFileItem()->skipBytes(4*4);
            }

            break;
        default:
            throw Exception("MapFileType::_readObject() - unknown type");
            break;
    }
    return object;
}

DatFileItem * MapFileType::datFileItem()
{
    return _datFileItem;
}

std::vector<MapElevation *> * MapFileType::elevations()
{
    return _elevations;
}

unsigned int MapFileType::defaultPosition()
{
    return _defaultPosition;
}

unsigned int MapFileType::defaultElevation()
{
    return _defaultElevation;
}

unsigned int MapFileType::defaultOrientation()
{
    return _defaultOrientaion;
}

}
