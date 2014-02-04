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

#ifndef LIBFALLTERGEIST_GAMFILETYPE_H
#define LIBFALLTERGEIST_GAMFILETYPE_H

// C++ standard includes
#include <map>
#include <string>

// libfalltergeist includes
#include "../src/DatFileItem.h"

// Third party includes

namespace libfalltergeist
{

class GamFileType : public DatFileItem
{
protected:
    std::map<std::string, int> _GVARS;
    std::map<std::string, int> _MVARS;
    virtual void _initialize();
    bool _GVARmode = false;
    bool _MVARmode = false;
    void _parseLine(std::string line);
public:
    GamFileType(DatFileEntry* datFileEntry);
    GamFileType(std::ifstream* stream);
    virtual ~GamFileType();
    std::map<std::string, int>* GVARS();
    std::map<std::string, int>* MVARS();
    int GVAR(std::string name);
    int GVAR(unsigned int number);
    int MVAR(std::string name);
    int MVAR(unsigned int number);
};

}
#endif // LIBFALLTERGEIST_GAMFILETYPE_H
