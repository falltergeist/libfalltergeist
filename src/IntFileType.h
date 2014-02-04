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

#ifndef LIBFALLTERGEIST_INTFILETYPE_H
#define LIBFALLTERGEIST_INTFILETYPE_H

// C++ standard includes
#include <map>
#include <vector>
#include <string>

// libfalltergeist includes
#include "../src/DatFileItem.h"

// Third party includes

namespace libfalltergeist
{

class IntFileType : public DatFileItem
{
protected:
    std::map<unsigned int, std::string> _functions;
    std::vector<unsigned int> _functionsOffsets;
    std::map<unsigned int, std::string> _identificators;
    std::map<unsigned int, std::string> _strings;
    virtual void _initialize();
public:
    IntFileType(DatFileEntry * datFileEntry);
    IntFileType(std::ifstream * stream);
    virtual ~IntFileType();

    unsigned int function(std::string name);
    unsigned int function(unsigned int index);

    std::map<unsigned int, std::string>* identificators();
    std::map<unsigned int, std::string>* strings();
};

}
#endif // LIBFALLTERGEIST_INTFILETYPE_H
