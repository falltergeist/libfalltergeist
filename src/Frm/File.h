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
#include "../Enums.h"

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

class File : public Dat::Item
{

public:

    File(Dat::Entry* datFileEntry);
    File(std::ifstream* stream);
    ~File();

    uint32_t version() const;
    uint16_t framesPerSecond() const;
    uint16_t framesPerDirection() const;
    uint16_t actionFrame() const;

    uint16_t width() const;
    uint16_t width(unsigned int direction) const;
    uint16_t width(unsigned int direction, unsigned int frame) const;

    uint16_t height() const;
    uint16_t height(unsigned int direction) const;
    uint16_t height(unsigned int direction, unsigned int frame) const;

    int16_t offsetX(unsigned int direction = 0, unsigned int frame = 0) const;
    int16_t offsetY(unsigned int direction = 0, unsigned int frame = 0) const;

    uint32_t* rgba(Pal::File* palFile);
    bool animatedPalette();
    std::map<MASK, uint8_t*>* animatedMasks();
    std::vector<Direction*>* directions();

protected:
    uint32_t* _rgba = 0;
    uint32_t _version = 0;
    uint16_t _framesPerSecond = 0;
    uint16_t _framesPerDirection = 0;
    uint16_t _actionFrame = 0;
    bool _animatedPalette = false;
    std::map<MASK, uint8_t*> _animatedMasks;
    std::vector<Direction*> _directions;
    virtual void _initialize();

};

}
}
#endif // LIBFALLTERGEIST_FRM_FILE_H
