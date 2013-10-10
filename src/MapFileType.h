#ifndef LIBFALLTERGEIST_MAPFILETYPE_H
#define LIBFALLTERGEIST_MAPFILETYPE_H

#include <string>
#include <vector>

namespace libfalltergeist
{

class DatFileItem;
class MapElevation;
class ProFileType;
class MapObject;

typedef ProFileType * (*ProFileTypeLoaderCallback)(unsigned int);

class MapFileType
{
protected:
    ProFileTypeLoaderCallback _proFileTypeLoaderCallback;

    DatFileItem * _datFileItem;
    std::vector<MapElevation *> * _elevations;
    unsigned int _version;
    std::string _name;
    unsigned int _defaultPosition;
    unsigned int _defaultElevation;
    unsigned int _defaultOrientaion;
    unsigned int _localVarsNumber;
    unsigned int _globalVarsNumber;
    unsigned int _elevationsFlag;
    unsigned int _mapId;
    unsigned int _timeTicks;

    int _scriptId;

    MapObject * _readObject();

public:
    MapFileType(DatFileItem * datFileItem, ProFileTypeLoaderCallback callback);
    ~MapFileType();

    void open();

    DatFileItem * datFileItem();
};


}

#endif // LIBFALLTERGEIST_MAPFILETYPE_H
