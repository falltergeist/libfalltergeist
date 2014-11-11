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

#ifndef LIBFALLTERGEIST_MVEFILETYPE_H
#define LIBFALLTERGEIST_MVEFILETYPE_H

// C++ standard includes
#include <vector>

// libfalltergeist includes
#include "../src/DatFileItem.h"

// Third party includes

namespace libfalltergeist
{

struct MveOpcode
{
    uint16_t length;
    uint8_t type;
    uint8_t version;
    uint8_t* data;
};

class MveChunk
{
public:
    MveChunk() {}
    ~MveChunk();
    uint16_t length;
    uint16_t type;
    std::vector<std::shared_ptr<MveOpcode>> opcodes;
};

class MveFileType : public DatFileItem
{
protected:
    virtual void _initialize();
public:
    MveFileType(std::shared_ptr<DatFileEntry> datFileEntry);
    MveFileType(std::ifstream* stream);
    ~MveFileType();
    std::shared_ptr<MveChunk> getNextChunk();
};

}
#endif // LIBFALLTERGEIST_MVEFILETYPE_H
