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
    std::cout << "Objects total: " << objectsTotal << std::endl;

    for (unsigned int i = 0; i != elevations; ++i)
    {
        unsigned int objectsOnElevation = datFileItem()->readUint32();
        std::cout << "Objects on elevation: " << objectsOnElevation << std::endl;
        for (unsigned int j = 0; j != objectsOnElevation; ++j)
        {
            MapObject * object = _readObject();
            _elevations->at(i)->objects()->push_back(object);

            /*
            std::cout << std::endl << "Unknown 1: 0x" << std::hex << object->unknown1() << std::endl;
            std::cout << "Hex position: 0x" << std::hex << object->hexPosition() << std::endl;
            std::cout << "Unknown 2: 0x" << std::hex << object->unknown2() << std::endl;
            std::cout << "Unknown 3: 0x" << std::hex << object->unknown3() << std::endl;
            std::cout << "Unknown 4: 0x" << std::hex << object->unknown4() << std::endl;
            std::cout << "Unknown 5: 0x" << std::hex << object->unknown5() << std::endl;
            std::cout << "Frm Type Id: 0x" << std::hex << object->frmTypeId() << std::endl;
            std::cout << "Frm Id: 0x" << std::hex << object->frmId() << std::endl;
            std::cout << "Unknown 6: 0x" << std::hex << object->unknown6() << std::endl;
            std::cout << "Elevation: 0x" << std::hex << object->elevation() << std::endl;
            std::cout << "Object Type Id: 0x" << std::hex << object->objectTypeId() << std::endl;
            std::cout << "Object Id: 0x" << std::hex << object->objectId() << std::endl;
            std::cout << "Object Subtype Id: 0x" << std::hex << object->objectSubtypeId() << std::endl;
            std::cout << "Unknown 7: 0x" << std::hex << object->unknown7() << std::endl;
            std::cout << "Unknown 8: 0x" << std::hex << object->unknown8() << std::endl;
            std::cout << "Unknown 9: 0x" << std::hex << object->unknown9() << std::endl;
            std::cout << "Unknown 10: 0x" << std::hex << object->unknown10() << std::endl;
            std::cout << "Script Type Id: 0x" << std::hex << object->scriptTypeId() << std::endl;
            std::cout << "Script Id: 0x" << std::hex << object->scriptId() << std::endl;
            std::cout << "Map Script Id: 0x" << std::hex << object->mapScriptId() << std::endl;
            std::cout << "Inventory size: 0x" << std::hex << object->inventorySize() << std::endl;
            std::cout << "Unknown 11: 0x" << std::hex << object->unknown11() << std::endl;
            std::cout << "Unknown 12: 0x" << std::hex << object->unknown12() << std::endl;
            std::cout << "Unknown 13: 0x" << std::hex << object->unknown13() << std::endl;
            */

            //if (object->scriptTypeId() >= 0 && object->mapScriptId() >= 0)
            {
                //throw "123";
            }

            if (object->objectTypeId() != object->frmTypeId())
            {
                throw "123";
            }

            if (object->inventorySize() > 0)
            {
                //datFileItem()->readUint32(); //unknown
                //datFileItem()->skipBytes(4);

                for (unsigned int i = 0; i != object->inventorySize(); ++i)
                {
                    //j++;
                    //_readObject();
                    //datFileItem()->readUint32(); //unknown (items count?)
                    datFileItem()->skipBytes(4);
                    MapObject * obj = _readObject();
                   // datFileItem()->readUint32(); //unknown

                    /*
                    std::cout << std::endl << "-Unknown 2: 0x" << std::hex << obj->unknown2() << std::endl;
                    std::cout << "-Unknown 3: 0x" << std::hex << obj->unknown3() << std::endl;
                    std::cout << "-Unknown 4: 0x" << std::hex << obj->unknown4() << std::endl;
                    std::cout << "-Unknown 5: 0x" << std::hex << obj->unknown5() << std::endl;
                    std::cout << "-Frm Type Id: 0x" << std::hex << obj->frmTypeId() << std::endl;
                    std::cout << "-Frm Id: 0x" << std::hex << obj->frmId() << std::endl;
                    std::cout << "-Unknown 6: 0x" << std::hex << obj->unknown6() << std::endl;
                    std::cout << "-Elevation: 0x" << std::hex << obj->elevation() << std::endl;
                    std::cout << "-Object Type Id: 0x" << std::hex << obj->objectTypeId() << std::endl;
                    std::cout << "-Object Id: 0x" << std::hex << obj->objectId() << std::endl;
                    std::cout << "-Object Subtype Id: 0x" << std::hex << obj->objectSubtypeId() << std::endl;
                    std::cout << "-Unknown 7: 0x" << std::hex << obj->unknown7() << std::endl;
                    std::cout << "-Unknown 8: 0x" << std::hex << obj->unknown8() << std::endl;
                    std::cout << "-Unknown 9: 0x" << std::hex << obj->unknown9() << std::endl;
                    std::cout << "-Unknown 10: 0x" << std::hex << obj->unknown10() << std::endl;
                    std::cout << "-Script Type Id: 0x" << std::hex << obj->scriptTypeId() << std::endl;
                    std::cout << "-Script Id: 0x" << std::hex << obj->scriptId() << std::endl;
                    std::cout << "-Map Script Id: 0x" << std::hex << obj->mapScriptId() << std::endl;
                    std::cout << "-Inventory size: 0x" << std::hex << obj->inventorySize() << std::endl;
                    std::cout << "-Unknown 11: 0x" << std::hex << obj->unknown11() << std::endl;
                    std::cout << "-Unknown 12: 0x" << std::hex << obj->unknown12() << std::endl;
                    std::cout << "-Unknown 13: 0x" << std::hex << obj->unknown13() << std::endl;
                    */
                }
                //datFileItem()->readUint32(); //unknown
                //datFileItem()->skipBytes(8);

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
                case ProFileType::TYPE_ITEM_CONTAINER:
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
            break;
        case ProFileType::TYPE_SCENERY:
            object->setObjectSubtypeId(_proFileTypeLoaderCallback(PID)->objectSubtypeId());

            pr = _proFileTypeLoaderCallback(PID);
            if (pr->frmOffset() != 0)
            {
                std::cout << " FRM OFFSET " << pr->frmOffset() << std::endl;
            }

            if (object->objectId() == 0x11) break; //
            if (object->objectId() == 0x15) break; //
            if (object->objectId() == 0x96) break;
            if (object->objectId() == 0x1a5)
            {
                datFileItem()->skipBytes(4);
                break; //
            }
            if (object->objectId() == 0x43)  break; // SECRET BLOCKING HEX
            if (object->objectId() == 0x158) break; //Block Hex Auto Inviso
            if (object->objectId() == 840) break; //Stripe
            if (object->objectId() == 842) break; //Stripe
            if (object->objectId() == 843) break; //Stripe
            if (object->objectId() == 844) break; //Stripe
            if (object->objectId() == 845) break; //Stripe
            if (object->objectId() == 847) break; //Stripe
            if (object->objectId() == 0x8d) break; // ????

            //if (FID == 0x02000015) break; // block.frm
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

                    datFileItem()->skipBytes(4);
                    break;
                case ProFileType::TYPE_SCENERY_GENERIC:
                    if (object->objectId() == 0x50d) // Elevator Stub
                    {
                        datFileItem()->skipBytes(4*2);
                    }
                    break;
                default:
                    std::cout << "UNIDENTIFIED SCENERY" << std::endl;
                    throw ":(";
                    break;
            }
            break;
        case ProFileType::TYPE_WALL:
            //datFileItem()->skipBytes(4);
            break;
        case ProFileType::TYPE_TILE:
            break;
        case ProFileType::TYPE_MISC:
            switch (object->objectId())
            {
                case 0x10:
                case 0x11:  // EXIT ?
                case 0x12:
                case 0x13:
                case 0x14:
                case 0x15:
                case 0x17:
                case 0x18:
                case 0x21:
                    datFileItem()->skipBytes(4*4);
                    break;
                case 0xC: // BLOCK
                    break;
                default:
                    std::cout << "UNIDENTIFIED MISC" << std::endl;
                    //throw ":(";
                    break;
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
