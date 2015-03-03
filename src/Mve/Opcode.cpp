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
#include "../Mve/Opcode.h"

// Third party includes

namespace libfalltergeist
{
namespace Mve
{

Opcode::Opcode(uint16_t length)
{
    _length = length;
    _data = new uint8_t[_length];
}

Opcode::~Opcode()
{
    delete [] _data;
}

uint16_t Opcode::length() const
{
    return _length;
}

uint8_t Opcode::type() const
{
    return _type;
}

void Opcode::setType(uint8_t value)
{
    _type = value;
}

uint8_t Opcode::version() const
{
    return _version;
}

void Opcode::setVersion(uint8_t value)
{
    _version = value;
}

uint8_t* Opcode::data() const
{
    return _data;
}



}
}
