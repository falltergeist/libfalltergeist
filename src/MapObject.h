#ifndef LIBFALLTERGEIST_MAPOBJECT_H
#define LIBFALLTERGEIST_MAPOBJECT_H

namespace libfalltergeist
{

class MapObject
{
protected:
    unsigned int _unknown1;
             int _hexPosition;
    unsigned int _unknown2;
    unsigned int _unknown3;
    unsigned int _unknown4;
    unsigned int _unknown5;
    unsigned int _frameNumber;
    unsigned int _orientation;
    unsigned int _frmTypeId;
    unsigned int _frmId;
    unsigned int _unknown6;
    unsigned int _elevation;
    unsigned int _objectTypeId;
    unsigned int _objectId;
    unsigned int _objectSubtypeId;
    unsigned int _objectID1;
    unsigned int _objectID2;
    unsigned int _objectID3;
    unsigned int _unknown7;
    unsigned int _unknown8;
    unsigned int _unknown9;
    unsigned int _unknown10;
             int _scriptTypeId;
    unsigned int _scriptId;
             int _mapScriptId;
    unsigned int _inventorySize;
    unsigned int _unknown11;
    unsigned int _unknown12;
    unsigned int _unknown13;
public:
    MapObject();
    ~MapObject();

    unsigned int unknown1();
    void setUnknown1(unsigned int value);
    int hexPosition();
    void setHexPosition(int value);
    unsigned int unknown2();
    void setUnknown2(unsigned int value);
    unsigned int unknown3();
    void setUnknown3(unsigned int value);
    unsigned int unknown4();
    void setUnknown4(unsigned int value);
    unsigned int unknown5();
    void setUnknown5(unsigned int value);
    unsigned int frameNumber();
    void setFrameNumber(unsigned int value);
    unsigned int orientation();
    void setOrientation(unsigned int value);
    unsigned int frmTypeId();
    void setFrmTypeId(unsigned int value);
    unsigned int frmId();
    void setFrmId(unsigned int value);
    unsigned int unknown6();
    void setUnknown6(unsigned int value);
    unsigned int elevation();
    void setElevation(unsigned int value);
    unsigned int objectTypeId();
    void setObjectTypeId(unsigned int value);
    unsigned int objectId();
    void setObjectId(unsigned int value);
    unsigned int objectSubtypeId();
    void setObjectSubtypeId(unsigned int value);
    unsigned int objectID1();
    void setObjectID1(unsigned int value);
    unsigned int objectID2();
    void setObjectID2(unsigned int value);
    unsigned int objectID3();
    void setObjectID3(unsigned int value);
    unsigned int unknown7();
    void setUnknown7(unsigned int value);
    unsigned int unknown8();
    void setUnknown8(unsigned int value);
    unsigned int unknown9();
    void setUnknown9(unsigned int value);
    unsigned int unknown10();
    void setUnknown10(unsigned int value);
    int scriptTypeId();
    void setScriptTypeId(int value);
    unsigned int scriptId();
    void setScriptId(unsigned int value);
    int mapScriptId();
    void setMapScriptId(int value);
    unsigned int inventorySize();
    void setInventorySize(unsigned int value);
    unsigned int unknown11();
    void setUnknown11(unsigned int value);
    unsigned int unknown12();
    void setUnknown12(unsigned int value);
    unsigned int unknown13();
    void setUnknown13(unsigned int value);

};

}
#endif // LIBFALLTERGEIST_MAPOBJECT_H
