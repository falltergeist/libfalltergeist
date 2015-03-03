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

// C++ standard includes

// libfalltergeist includes
#include "../Mve/Chunk.h"

// Third party includes

namespace libfalltergeist
{
namespace Mve
{

Chunk::Chunk()
{
}

Chunk::~Chunk()
{
    for (auto opcode : _opcodes)
    {
        delete opcode;
    }
}

uint16_t Chunk::length() const
{
    return _length;
}

void Chunk::setLength(uint16_t value)
{
    _length = value;
}

uint16_t Chunk::type() const
{
    return _type;
}

void Chunk::setType(uint16_t value)
{
    _type = value;
}

std::vector<Opcode*>* Chunk::opcodes()
{
    return &_opcodes;
}

}
}
