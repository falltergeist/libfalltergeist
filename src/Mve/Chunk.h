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

#ifndef LIBFALLTERGEIST_MVE_CHUNK_H
#define LIBFALLTERGEIST_MVE_CHUNK_H

// C++ standard includes
#include <memory>
#include <vector>

// libfalltergeist includes
#include "../Mve/Opcode.h"

// Third party includes

namespace libfalltergeist
{
namespace Mve
{

class Chunk
{

public:
    Chunk();
    ~Chunk();

    uint16_t length() const;
    void setLength(uint16_t value);

    uint16_t type() const;
    void setType(uint16_t value);

    std::vector<Opcode*>* opcodes();

protected:
    uint16_t _length;
    uint16_t _type;
    std::vector<Opcode*> _opcodes;

};

}
}
#endif // LIBFALLTERGEIST_MVE_CHUNK_H
