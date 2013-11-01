/*
 * Copyright 2012-2013 Falltergeist Developers.
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

#ifndef LIBFALLTERGEIST_LSTFILETYPE_H
#define LIBFALLTERGEIST_LSTFILETYPE_H

// C++ standard includes
#include <string>
#include <vector>

// libfalltergeist includes
#include "../src/DatFileItem.h"

// Third party includes

namespace libfalltergeist
{

class LstFileType : public DatFileItem
{
protected:
    std::vector<std::string> _strings;
    virtual void _initialize();
public:
    LstFileType(DatFileEntry* datFileEntry);
    LstFileType(std::ifstream* stream);
    ~LstFileType();

    std::vector<std::string>* strings();
};

}
#endif // LIBFALLTERGEIST_LSTFILETYPE_H
