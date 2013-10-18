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
            item >> _elevations->back()->roofTiles[i];
            item >>_elevations->back()->floorTiles[i];
        }
    }
    // SCRIPTS SECTION
    for (unsigned int i = 0; i < 5; i++)
    {
        short count = datFileItem()->readInt32();
        if (count > 0)
        {
            short loop = count;
            if (count%16 > 0 ) loop += 16 - count%16;

            int check = 0;
            for (unsigned short j = 0; j < loop; j++)
            {
                {
                    unsigned int PID = datFileItem()->readUint8();
                    datFileItem()->skipBytes(3);
                    switch (PID)
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
                    unsigned int v = datFileItem()->readUint32();
                    check += v;

                    datFileItem()->readInt32();
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
    int objectsTotal = datFileItem()->readInt32();

    for (unsigned int i = 0; i != elevations; ++i)
    {
        unsigned int objectsOnElevation = datFileItem()->readUint32();
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
                    MapObject * obj = _readObject();

                }

            }

        }
    }

}

MapObject * MapFileType::_readObject()
{
    MapObject * object = new MapObject();

    object->setUnknown1( datFileItem()->readUint32() );
    object->setHexPosition( datFileItem()->readInt32() );
    object->setUnknown2( datFileItem()->readUint32() );
    object->setUnknown3( datFileItem()->readUint32() );
    object->setUnknown4( datFileItem()->readUint32() );
    object->setUnknown5( datFileItem()->readUint32() );
    object->setFrameNumber( datFileItem()->readUint32() );
    object->setOrientation( datFileItem()->readUint32() );
    unsigned int FID = datFileItem()->readUint32();
    object->setFrmTypeId( FID >> 24 );
    object->setFrmId( 0x00FFFFFF & FID );
    object->setUnknown6( datFileItem()->readUint32() );
    object->setElevation( datFileItem()->readUint32() );
    unsigned int PID = datFileItem()->readInt32();
    object->setObjectTypeId( PID >> 24 );
    object->setObjectId( 0x00FFFFFF & PID);
    object->setUnknown7( datFileItem()->readUint32() );
    object->setUnknown8( datFileItem()->readUint32() );
    object->setUnknown9( datFileItem()->readUint32() );
    object->setUnknown10( datFileItem()->readUint32() );
    unsigned int SID = datFileItem()->readInt32();
    object->setScriptTypeId(SID >> 24);
    object->setScriptId( 0x00FFFFFF & SID);
    object->setMapScriptId( datFileItem()->readInt32() );
    object->setInventorySize( datFileItem()->readUint32() );
    object->setUnknown11( datFileItem()->readUint32() );
    object->setUnknown12( datFileItem()->readUint32() );
    object->setUnknown13( datFileItem()->readUint32() );

    ProFileType * pr ;

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
