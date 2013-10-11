#ifndef LIBFALLTERGEIST_MAPELEVATION_H
#define LIBFALLTERGEIST_MAPELEVATION_H

#include <list>

namespace libfalltergeist
{
class MapObject;

class MapElevation
{
protected:
public:
    unsigned short floorTiles[10000];
    unsigned short roofTiles[10000];
    std::list<MapObject *> * _objects;
    MapElevation();
    ~MapElevation();
    std::list<MapObject *> * objects();
};

}

#endif // LIBFALLTERGEIST_MAPELEVATION_H
