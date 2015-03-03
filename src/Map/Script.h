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

#ifndef LIBFALLTERGEIST_MAP_SCRIPT_H
#define LIBFALLTERGEIST_MAP_SCRIPT_H

// C++ standard includes
#include <cstdint>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
namespace Map
{

class Script
{

public:
    Script();
    ~Script();

    int32_t PID() const;
    void setPID(int32_t PID);

    int32_t scriptId() const;
    void setScriptId(int32_t value);

protected:
    int32_t _PID = 0;
    int32_t _scriptId = -1;
    int32_t _unknown1 = 0;
    int32_t _unknown2 = 0;
    int32_t _unknown3 = 0;
    int32_t _unknown4 = 0;
    int32_t _unknown5 = 0;
    int32_t _unknown6 = 0;
    int32_t _unknown7 = 0;
    int32_t _unknown8 = 0;
    int32_t _unknown9 = 0;
    int32_t _unknown10 = 0;
    int32_t _unknown11 = 0;
    int32_t _unknown12 = 0;
    int32_t _unknown13 = 0;
    int32_t _unknown14 = 0;
    int32_t _unknown15 = 0;
    int32_t _unknown16 = 0;

};

}
}
#endif // LIBFALLTERGEIST_MAP_SCRIPT_H
