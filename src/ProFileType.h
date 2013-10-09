#ifndef LIBFALLTERGEIST_PROFILETYPE_H
#define LIBFALLTERGEIST_PROFILETYPE_H

namespace libfalltergeist
{
class DatFileItem;

class ProFileType
{
protected:
    DatFileItem * _datFileItem;
    unsigned int _objectTypeId;
    unsigned int _objectSubtypeId;
    unsigned int _objectId;
    unsigned int _messageId;
    unsigned int _frmType;
    unsigned int _frmId;

public:
    enum { TYPE_ITEMS = 0, TYPE_CRITTERS, TYPE_SCENERY, TYPE_WALLS, TYPE_TILES, TYPE_MISC };
    enum { TYPE_ITEMS_ARMOR = 0, TYPE_ITEMS_CONTAINER, TYPE_ITEMS_DRUG, TYPE_ITEMS_WEAPON, TYPE_ITEMS_AMMO, TYPE_ITEMS_MISC, TYPE_ITEMS_KEY };
    enum { TYPE_SCENERY_DOOR = 0, TYPE_SCENERY_STAIRS, TYPE_SCENERY_ELEVATIOR, TYPE_SCENERY_LADDER_BOTTOM, TYPE_SCENERY_LADDER_TOP, TYPE_SCENERY_GENERIC };

    ProFileType(DatFileItem * datFileItem);
    ~ProFileType();

    DatFileItem * datFileItem();

    void open();

};
}

#endif // LIBFALLTERGEIST_PROFILETYPE_H
