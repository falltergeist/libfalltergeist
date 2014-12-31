/*
 * Copyright 2012-2015 Falltergeist Developers.
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

// C++ standard includes
#include <vector>
#include <map>

// libfalltergeist includes
#include "../src/DatFileItem.h"

// Third party includes

namespace libfalltergeist
{
class PalFileType;


class FrmFileType : public DatFileItem
{
protected:
    unsigned int* _rgba = 0;
    std::map<unsigned int, uint8_t*> _animatedMasks;
    unsigned int _directions = 0;
    signed short _shiftX[6];
    signed short _shiftY[6];
    unsigned int _dataOffset[6];
    std::vector<unsigned int> _width[6];
    std::vector<unsigned int> _height[6];
    std::vector<signed short> _offsetX[6];
    std::vector<signed short> _offsetY[6];
    std::vector<unsigned int> _positionX[6]; // frame image position in rgba image
    std::vector<unsigned int> _positionY[6];
    unsigned int _version;
    unsigned short _framesPerSecond;
    unsigned short _framesPerDirection;
    unsigned short _actionFrame;
    virtual void _initialize();
    bool _animatedPalette;
public:
    enum { TYPE_ITEM = 0, TYPE_CRITTER, TYPE_SCENERY, TYPE_WALL, TYPE_TILE, TYPE_BACKGROUND, TYPE_INTERFACE, TYPE_INVENTORY };

    enum {
        MASK_SLIME = 0,
        MASK_FIRE_SLOW = 2,
        MASK_FIRE_FAST = 4,
        MASK_MONITOR = 8,
        MASK_REDDOT = 16,
        MASK_SHORE = 32
    };

    FrmFileType(std::shared_ptr<DatFileEntry> datFileEntry);
    FrmFileType(std::ifstream* stream);
    ~FrmFileType();

    unsigned int version();

    unsigned short framesPerSecond();

    unsigned short framesPerDirection();

    unsigned short actionFrame();

    unsigned int directions();

    unsigned int width();
    unsigned int width(unsigned int direction);
    unsigned int width(unsigned int direction, unsigned int frame);

    unsigned int height();
    unsigned int height(unsigned int direction);
    unsigned int height(unsigned int direction, unsigned int frame);

    int offsetX(unsigned int direction = 0, unsigned int frame = 0);
    int offsetY(unsigned int direction = 0, unsigned int frame = 0);

    int shiftX(unsigned int direction);
    int shiftY(unsigned int direction);

    unsigned int* rgba(std::shared_ptr<PalFileType> palFile);
    bool animatedPalette();
    std::map<unsigned int, uint8_t*>*  animatedMasks();
};

}
#endif // LIBFALLTERGEIST_FRMFILETYPE_H
