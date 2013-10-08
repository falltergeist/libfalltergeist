#include "../src/MapFileType.h"
#include "../src/DatFileItem.h"

#include <iostream>

namespace libfalltergeist
{

MapFileType::MapFileType(DatFileItem * datFileItem) : _datFileItem(datFileItem)
{
    open();
}

MapFileType::~MapFileType()
{
}

void MapFileType::open()
{
    datFileItem()->setPosition(0);
    _version = datFileItem()->readUint32();
    std::cout << "Version: " << _version << std::endl;

    char * buffer = new char[17]();
    datFileItem()->readBytes(buffer, 16);
    _name += buffer;
    delete [] buffer;
    std::cout << "Name: " << _name << std::endl;

    _defaultPosition = datFileItem()->readUint32();
    _defaultElevation = datFileItem()->readUint32();
    _defaultOrientaion = datFileItem()->readUint32();

    std::cout << "Default Position: " << _defaultPosition << std::endl;
    std::cout << "Default Elevation: " << _defaultElevation << std::endl;
    std::cout << "Default Orientaion: " << _defaultOrientaion << std::endl;

    _localVarsNumber = datFileItem()->readUint32();
    _scriptId = datFileItem()->readInt32();

    std::cout << "Local Vars: " << _localVarsNumber << std::endl;
    std::cout << "Script Id: " << _scriptId << std::endl;

    _elevationsFlag = datFileItem()->readUint32();
    if (_elevationsFlag & 0x1 == 0)
    {
        std::cout << "Elevation Flag: UNKNOWN" << std::endl;
    }
    if (_elevationsFlag & 0x2 == 0)
    {
        std::cout << "Elevation Flag: 0" << std::endl;
    }
    if (_elevationsFlag & 0x4 == 0)
    {
        std::cout << "Elevation Flag: 1" << std::endl;
    }
    if (_elevationsFlag & 0x8 == 0)
    {
        std::cout << "Elevation Flag: 2" << std::endl;
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

    //global variables
    datFileItem()->skipBytes(4*_globalVarsNumber);

    //local variables
    datFileItem()->skipBytes(4*_localVarsNumber);


    // TILES

}

DatFileItem * MapFileType::datFileItem()
{
    return _datFileItem;
}

}
