#include "../src/MapFileType.h"
#include "../src/DatFileItem.h"
#include "../src/MapElevation.h"
#include "../src/MapObject.h"
#include "../src/ProFileType.h"

#include <iostream>

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
    // HEADER
    datFileItem()->setPosition(0);
    _version = datFileItem()->readUint32();

    char * buffer = new char[17]();
    datFileItem()->readBytes(buffer, 16);
    _name += buffer;
    delete [] buffer;

    _defaultPosition = datFileItem()->readUint32();
    _defaultElevation = datFileItem()->readUint32();
    _defaultOrientaion = datFileItem()->readUint32();


    _localVarsNumber = datFileItem()->readUint32();
    _scriptId = datFileItem()->readInt32();

    std::cout << "Version: " << _version << std::endl;
    std::cout << "Name: " << _name << std::endl;
    std::cout << "Default Position: " << _defaultPosition << std::endl;
    std::cout << "Default Elevation: " << _defaultElevation << std::endl;
    std::cout << "Default Orientaion: " << _defaultOrientaion << std::endl;
    std::cout << "Local Vars: " << _localVarsNumber << std::endl;
    std::cout << "Script Id: " << _scriptId << std::endl;

    _elevationsFlag = datFileItem()->readUint32();
    std::cout << "Elevations flag: " << _elevationsFlag << std::endl;
    unsigned int elevations = 0;
    if ((_elevationsFlag & 1) == 0  )
    {
        std::cout << "Elevation Flag: UNKNOWN" << std::endl;
    }
    if ((_elevationsFlag & 2) == 0)
    {
        std::cout << "Elevation Flag: 0" << std::endl;
        elevations++;
    }
    if ((_elevationsFlag & 4) == 0)
    {
        std::cout << "Elevation Flag: 1" << std::endl;
        elevations++;
    }
    if ((_elevationsFlag & 8) == 0)
    {
        std::cout << "Elevation Flag: 2" << std::endl;
        elevations++;
    }

    //unknown 4 bytes
    datFileItem()->skipBytes(4);


    _globalVarsNumber = datFileItem()->readUint32();
    std::cout << "Global Vars: " << _globalVarsNumber << std::endl;

    _mapId = datFileItem()->readUint32();
    std::cout << "Map Id: " << _mapId << std::endl;

    _timeTicks = datFileItem()->readUint32();
    std::cout << "Time ticks: " << _timeTicks << std::endl;

    // unkonwn
    datFileItem()->skipBytes(4*44);

    // GLOBAL AND LOCAL VARS SECTION

    //global variables
    datFileItem()->skipBytes(4*_globalVarsNumber);    

    //local variables
    datFileItem()->skipBytes(4*_localVarsNumber);

    // TILES SECTION

    for (unsigned int i = 0; i < elevations; i++)
    {
        _elevations->push_back(new MapElevation);

        for (unsigned int i = 0; i < 10000; i++)
        {
            _elevations->back()->roofTiles[i] = datFileItem()->readUint16();
            _elevations->back()->floorTiles[i] = datFileItem()->readUint16();

            //std::cout << "Roof " << i << ": " << _elevations->back()->roofTiles[i] << std::endl;
            //std::cout << "Floo " << i << ": " << _elevations->back()->floorTiles[i] << std::endl;

        }
    }
    //datFileItem()->skipBytes(4*3);
    // SCRIPTS SECTION
    for (unsigned int i = 0; i < 5; i++)
    {
        /* number of scripts used in this sequence */
        short count = datFileItem()->readInt32();
        std::cout << "COUNT: " << count << std::endl;
        if (count > 0)
        {
            /* loop counter must be modulo 16 (rounded up) */
            short loop = count;
            if (count%16 > 0 ) loop += 16 - count%16;
            //std::cout << "LOOP: " << loop << std::endl;

            int check = 0;
            /* read in all the scripts of this sequence */
            for (unsigned short j = 0; j < loop; j++)
            {
                //READING SCRIPT
                // skipping script data for now...
                {
                    unsigned int PID = datFileItem()->readUint8();
                    datFileItem()->skipBytes(3);
                    //std::cout << PID << std::endl;
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

                /* after every 16 scripts is the check block */
                if ((j % 16) == 15)
                {
                    unsigned int v = datFileItem()->readUint32();
                    //std::cout << "V: " << v << std::endl;
                    check += v;

                    /* don't know what this is for, so ignore it for now */
                    datFileItem()->readInt32();
                }
             }
             if (check != count)
             {
                 std::cout << "error reading scripts: check is incorrect" << std::endl;
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
                    MapObject * obj = _readObject(true);

                }

            }

        }
    }

}

MapObject * MapFileType::_readObject(bool child)
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
                    std::cout << "UNIDENTIFIED ITEM" << std::endl;
                    throw ":(";
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
                    std::cout << "UNIDENTIFIED SCENERY" << std::endl;
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
            std::cout << "UNIDENTIFIED TYPE" << std::endl;
            //throw ":(";
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
