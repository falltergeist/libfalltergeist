/*
 * Copyright 2012-2013 Falltergeist Developers.
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

#ifndef LIBFALLTERGEIST_FRMFILETYPE_H
#define LIBFALLTERGEIST_FRMFILETYPE_H

#include <vector>

namespace libfalltergeist
{
class DatFileItem;
class FrmDirection;

class FrmFileType
{
protected:
    DatFileItem * _datFileItem;
    std::vector<FrmDirection *> * _directions;
    unsigned int _version; // FRM file version
    unsigned short _framesPerSecond; // Animation frame rate
    unsigned short _framesPerDirection; // Frames per direction
    unsigned short _actionFrame; // Number of frame on which action is occurs
public:


    enum { TYPE_ITEM = 0, TYPE_CRITTER, TYPE_SCENERY, TYPE_WALL, TYPE_TILE, TYPE_BACKGROUND, TYPE_INTERFACE, TYPE_INVENTORY };

    FrmFileType(DatFileItem * datFileItem);
    ~FrmFileType();

    DatFileItem * datFileItem();

    void open();

    void setVersion(unsigned int version);
    unsigned int version();

    void setFramesPerSecond(unsigned short fps);
    unsigned short framesPerSecond();

    void setFramesPerDirection(unsigned short fpd);
    unsigned short framesPerDirection();

    void setActionFrame(unsigned short number);
    unsigned short actionFrame();

    std::vector<FrmDirection *> * directions();

};

}
#endif // LIBFALLTERGEIST_FRMFILETYPE_H
