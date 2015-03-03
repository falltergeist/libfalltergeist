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

    uint32_t version() const;
    uint16_t framesPerSecond() const;
    uint16_t framesPerDirection() const;
    uint16_t actionFrame() const;

    std::vector<Direction*>* directions();

    uint16_t width() const;
    uint16_t width(unsigned int direction) const;
    uint16_t width(unsigned int direction, unsigned int frame) const;

    uint16_t height() const;
    uint16_t height(unsigned int direction) const;
    uint16_t height(unsigned int direction, unsigned int frame) const;

    uint16_t offsetX(unsigned int direction = 0, unsigned int frame = 0) const;
    uint16_t offsetY(unsigned int direction = 0, unsigned int frame = 0) const;

    uint16_t shiftX(unsigned int direction) const;
    uint16_t shiftY(unsigned int direction) const;

    uint32_t* rgba(std::shared_ptr<Pal::File> palFile);
    bool animatedPalette();
    std::map<unsigned int, uint8_t*>*  animatedMasks();

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

};

}
}
#endif // LIBFALLTERGEIST_FRM_FILE_H
