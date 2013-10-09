#include "../src/MapFileType.h"
#include "../src/DatFileItem.h"
#include "../src/MapElevation.h"
#include "../src/ProFileType.h"

#include <iostream>

namespace libfalltergeist
{

MapFileType::MapFileType(DatFileItem * datFileItem) : _datFileItem(datFileItem)
{
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
            datFileItem()->skipBytes(4); // unknown
            int hexPosition = datFileItem()->readInt32();
            std::cout << "Hex Position: " << hexPosition << std::endl;
            datFileItem()->skipBytes(4*4); // unknown
            unsigned int frameNumber = datFileItem()->readUint32();
            std::cout << "Frame number: " << frameNumber << std::endl;
            unsigned int orientation = datFileItem()->readUint32();
            std::cout << "Orientation: " << orientation << std::endl;
            unsigned int FID = datFileItem()->readUint32();
            std::cout << "FID: 0x" << std::hex << FID << std::endl;
            datFileItem()->skipBytes(4); // flags?
            unsigned int mapElevation = datFileItem()->readUint32();
            std::cout << "Map Elevation: " << mapElevation << std::endl;
            int PID = datFileItem()->readInt32();
            std::cout << "PID: 0x" << std::hex << PID << std::endl;
            datFileItem()->skipBytes(4*4); //unknown
            int SID = datFileItem()->readInt32();
            std::cout << "SID: 0x" << std::hex << SID << std::endl;
            int scriptId = datFileItem()->readInt32();
            std::cout << "Script Id: " << scriptId << std::endl;
            unsigned int inventorySize = datFileItem()->readUint32();
            std::cout << "Inventory size: " << inventorySize << std::endl;
            datFileItem()->skipBytes(4*3); //unknown

            switch (PID >> 24)
            {
                case ProFileType::TYPE_ITEMS:
                    break;
                case ProFileType::TYPE_CRITTERS:
                    datFileItem()->skipBytes(10*4);
                    break;
                case ProFileType::TYPE_SCENERY:
                    //datFileItem()->skip
                    break;
                case ProFileType::TYPE_WALLS:
                    break;
                case ProFileType::TYPE_TILES:
                    break;
                case ProFileType::TYPE_MISC:
                    break;
            }


            return;
        }
    }


}

DatFileItem * MapFileType::datFileItem()
{
    return _datFileItem;
}

}
