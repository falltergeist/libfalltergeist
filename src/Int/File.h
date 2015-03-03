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

#ifndef LIBFALLTERGEIST_INT_FILE_H
#define LIBFALLTERGEIST_INT_FILE_H

// C++ standard includes
#include <map>
#include <string>
#include <vector>

// libfalltergeist includes
#include "../Dat/Item.h"

// Third party includes

namespace libfalltergeist
{
namespace Int
{
class Procedure;

class File : public Dat::Item
{

public:
    File(std::shared_ptr<Dat::Entry> datFileEntry);
    File(std::ifstream * stream);
    virtual ~File();

    std::vector<Procedure*>* procedures();
    Procedure* procedure(std::string name);

    std::map<unsigned int, std::string>* identifiers();
    std::map<unsigned int, std::string>* strings();

protected:
    std::vector<Procedure*> _procedures;

    std::map<unsigned int, std::string> _functions;
    std::vector<unsigned int> _functionsOffsets;
    std::map<unsigned int, std::string> _identifiers;
    std::map<unsigned int, std::string> _strings;
    virtual void _initialize();

};

}
}
#endif // LIBFALLTERGEIST_INT_FILE_H
