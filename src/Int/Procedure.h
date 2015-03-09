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

#ifndef LIBFALLTERGEIST_INT_PROCEDURE_H
#define LIBFALLTERGEIST_INT_PROCEDURE_H

// C++ standard includes
#include <cstdint>
#include <string>

// libfalltergeist includes
#include "../Enums.h"

// Third party includes

namespace libfalltergeist
{
namespace Int
{

class Procedure
{

public:
    Procedure();       

    uint32_t flags() const;
    void setFlags(uint32_t flags);

    uint32_t delay() const;
    void setDelay(uint32_t delay);

    uint32_t conditionOffset() const;
    void setConditionOffset(uint32_t offset);

    uint32_t bodyOffset() const;
    void setBodyOffset(uint32_t offset);

    uint32_t argumentsCounter();
    void setArgumentsCounter(uint32_t value);

    std::string name() const;
    void setName(const std::string& name);

    bool isTimed();
    bool isConditional();
    bool isImported();
    bool isExported();
    bool isCritical();
    bool isPure();
    bool isInline();

protected:
    std::string _name;
    uint32_t _flags = 0;
    uint32_t _delay = 0; // delay for timed procedures
    uint32_t _conditionOffset = 0; // offset of condition in code for conditional procedures
    uint32_t _bodyOffset = 0; // procedure body offset from the beginning of the file
    uint32_t _argumentsCounter = 0; // number of arguments

};

}
}
#endif // LIBFALLTERGEIST_INT_PROCEDURE_H
