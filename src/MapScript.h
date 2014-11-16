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

#ifndef LIBFALLTERGEIST_MAPSCRIPT_H
#define LIBFALLTERGEIST_MAPSCRIPT_H

// C++ standard includes

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{

class MapScript
{
protected:
    int _PID;
    int _unknown1,
        _unknown2,
        _unknown3,
        _unknown4,
        _unknown5,
        _unknown6,
        _unknown7,
        _unknown8,
        _unknown9,
        _unknown10,
        _unknown11,
        _unknown12,
        _unknown13,
        _unknown14,
        _unknown15,
        _unknown16;
    int _scriptId;
public:
    MapScript();
    ~MapScript();

    int PID();
    void setPID(int PID);
    int scriptId();
    void setScriptId(int value);
};

}
#endif // LIBFALLTERGEIST_MAPSCRIPT_H
