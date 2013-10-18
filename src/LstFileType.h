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

// Third party includes

namespace libfalltergeist
{
class DatFileItem;

class LstFileType
{
protected:
    DatFileItem * _datFileItem;
    std::vector<std::string> * _strings;
public:
    LstFileType(DatFileItem * datFileItem);
    ~LstFileType();

    DatFileItem * datFileItem();

    void open();

    std::vector<std::string> * strings();
};

}
#endif // LIBFALLTERGEIST_LSTFILETYPE_H
