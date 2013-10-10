#ifndef LIBFALLTERGEIST_MAPELEVATION_H
#define LIBFALLTERGEIST_MAPELEVATION_H

namespace libfalltergeist
{
class MapObject;

class MapElevation
{
protected:
public:
    unsigned short floorTiles[10000];
    unsigned short roofTiles[10000];
    MapElevation();
    ~MapElevation();
};

}

#endif // LIBFALLTERGEIST_MAPELEVATION_H
