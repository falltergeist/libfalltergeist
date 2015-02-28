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

#ifndef LIBFALLTERGEIST_FON_FILE_H
#define LIBFALLTERGEIST_FON_FILE_H

// C++ standard includes

// libfalltergeist includes
#include "../Dat/Item.h"

// Third party includes

namespace libfalltergeist
{
namespace Fon
{

class File : public Dat::Item
{
protected:
    virtual void _initialize();
public:
    File(std::shared_ptr<Dat::Entry> datFileEntry);
    File(std::ifstream* stream);
    virtual ~File();
};

}
}
#endif // LIBFALLTERGEIST_FON_FILE_H
