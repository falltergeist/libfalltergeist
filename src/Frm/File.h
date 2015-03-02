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

#ifndef LIBFALLTERGEIST_FRM_FILE_H
#define LIBFALLTERGEIST_FRM_FILE_H

// C++ standard includes
#include <map>
#include <vector>

// libfalltergeist includes
#include "../Dat/Item.h"

// Third party includes

namespace libfalltergeist
{
namespace Pal
{
    class File;
}
namespace Frm
{
class Direction;

enum FrmType
{
    TYPE_ITEM = 0,
    TYPE_CRITTER,
    TYPE_SCENERY,
    TYPE_WALL,
    TYPE_TILE,
    TYPE_MISC,
    TYPE_INTERFACE,
    TYPE_INVENTORY
};

class File : public Dat::Item
{
protected:
    uint32_t* _rgba = 0;
    std::map<unsigned int, uint8_t*> _animatedMasks;
    std::vector<Direction*> _directions;
    unsigned int _version;
    unsigned short _framesPerSecond;
    unsigned short _framesPerDirection;
    unsigned short _actionFrame;
    virtual void _initialize();
    bool _animatedPalette = false;
public:

    enum {
        MASK_SLIME = 0,
        MASK_FIRE_SLOW = 2,
        MASK_FIRE_FAST = 4,
        MASK_MONITOR = 8,
        MASK_REDDOT = 16,
        MASK_SHORE = 32
    };

    File(std::shared_ptr<Dat::Entry> datFileEntry);
    File(std::ifstream* stream);
    ~File();

    unsigned int version();

    unsigned short framesPerSecond();

    unsigned short framesPerDirection();

    unsigned short actionFrame();

    std::vector<Direction*>* directions();

    uint16_t width();
    uint16_t width(unsigned int direction);
    uint16_t width(unsigned int direction, unsigned int frame);

    uint16_t height();
    uint16_t height(unsigned int direction);
    uint16_t height(unsigned int direction, unsigned int frame);

    int offsetX(unsigned int direction = 0, unsigned int frame = 0);
    int offsetY(unsigned int direction = 0, unsigned int frame = 0);

    int shiftX(unsigned int direction);
    int shiftY(unsigned int direction);

    unsigned int* rgba(std::shared_ptr<Pal::File> palFile);
    bool animatedPalette();
    std::map<unsigned int, uint8_t*>*  animatedMasks();
};

}
}
#endif // LIBFALLTERGEIST_FRM_FILE_H
