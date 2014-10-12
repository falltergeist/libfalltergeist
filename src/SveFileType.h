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

#ifndef LIBFALLTERGEIST_SVEFILETYPE_H
#define LIBFALLTERGEIST_SVEFILETYPE_H

// C++ standard includes
#include <string>
#include <map>
#include <cstdint>

// libfalltergeist includes
#include "../src/DatFileItem.h"

// Third party includes

namespace libfalltergeist
{

class SveFileType : public DatFileItem
{
protected:
    virtual void _initialize();
public:
    SveFileType(std::shared_ptr<DatFileEntry> datFileEntry);
    SveFileType(std::ifstream* stream);
    ~SveFileType();
    std::pair<int,std::string> getSubLine(int frame);
private:
    std::map<int,std::string> _subs;
    void _addString(std::string line);
};

}
#endif // LIBFALLTERGEIST_SVEFILETYPE_H
