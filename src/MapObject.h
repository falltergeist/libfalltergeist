/*
 * Copyright 2012-2014 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBFALLTERGEIST_MAPOBJECT_H
#define LIBFALLTERGEIST_MAPOBJECT_H

// C++ standard includes
#include <vector>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{

class MapObject
{
protected:
    unsigned int _unknown1,
                 _unknown2,
                 _unknown3,
                 _unknown4,
                 _unknown5,
                 _frameNumber,
                 _orientation,
                 _frmTypeId,
                 _frmId,
                 _unknown6,
                 _elevation,
                 _objectTypeId = 0,
                 _objectId = 0,
                 _objectSubtypeId = 0,
                 _objectID1 = 0,
                 _objectID2 = 0,
                 _objectID3 = 0,
                 _unknown7,
                 _unknown8,
                 _unknown9,
                 _unknown10,
                 _inventorySize,
                 _unknown11,
                 _unknown12,
                 _unknown13;
    int _mapScriptId = -1,
        _scriptId = -1,
        _hexPosition = -1;
    std::vector<MapObject *> * _children;
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
    unsigned int FID();
    unsigned int frmTypeId();
    void setFrmTypeId(unsigned int value);
    unsigned int frmId();
    void setFrmId(unsigned int value);
    unsigned int unknown6();
    void setUnknown6(unsigned int value);
    unsigned int elevation();
    void setElevation(unsigned int value);
    unsigned int PID();
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
    int scriptId();
    void setScriptId(int value);
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

    std::vector<MapObject *> * children();
};

}
#endif // LIBFALLTERGEIST_MAPOBJECT_H
