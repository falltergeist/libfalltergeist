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
#include "../Int/Procedure.h"

// Third party includes

namespace libfalltergeist
{
namespace Int
{

Procedure::Procedure()
{
}

uint32_t Procedure::flags() const
{
    return _flags;
}

void Procedure::setFlags(uint32_t flags)
{
    _flags = flags;
}

uint32_t Procedure::delay() const
{
    return _delay;
}

void Procedure::setDelay(uint32_t delay)
{
    _delay = delay;
}

uint32_t Procedure::conditionOffset() const
{
    return _conditionOffset;
}

void Procedure::setConditionOffset(uint32_t offset)
{
    _conditionOffset = offset;
}

uint32_t Procedure::bodyOffset() const
{
    return _bodyOffset;
}

void Procedure::setBodyOffset(uint32_t offset)
{
    _bodyOffset = offset;
}

uint32_t Procedure::argumentsCounter()
{
    return _argumentsCounter;
}

void Procedure::setArgumentsCounter(uint32_t value)
{
    _argumentsCounter = value;
}

bool Procedure::isTimed()
{
    return flags() & ProcedureFlag::TIMED;
}

bool Procedure::isConditional()
{
    return flags() & ProcedureFlag::CONDITIONAL;
}

bool Procedure::isImported()
{
    return flags() & ProcedureFlag::IMPORTED;
}

bool Procedure::isExported()
{
    return flags() & ProcedureFlag::EXPORTED;
}

bool Procedure::isCritical()
{
    return flags() & ProcedureFlag::CRITICAL;
}

bool Procedure::isPure()
{
    return flags() & ProcedureFlag::PURE;
}

bool Procedure::isInline()
{
    return flags() & ProcedureFlag::INLINE;
}

std::string Procedure::name() const
{
    return _name;
}

void Procedure::setName(const std::string& name)
{
    _name = name;
}

}
}
