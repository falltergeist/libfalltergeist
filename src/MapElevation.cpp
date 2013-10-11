#include "../src/MapElevation.h"
#include "../src/MapObject.h"

namespace libfalltergeist
{

MapElevation::MapElevation()
{
    _objects = new std::list<MapObject *>;
}

MapElevation::~MapElevation()
{
    delete _objects;
}

std::list<MapObject *> * MapElevation::objects()
{
    return _objects;
}

}
