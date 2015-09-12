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

#ifndef FALLTERGEIST_TXT_BASEFILE_H
#define FALLTERGEIST_TXT_BASEFILE_H

// C++ standard includes
#include <list>

// Libfalltergeist includes
#include "../Dat/Item.h"

// Third party includes


namespace libfalltergeist
{
namespace Txt
{

/**
 * @brief Base class for all TXT file types.
 */
class BaseFile : public Dat::Item
{

public:
    BaseFile(std::ifstream* stream);
    BaseFile(Dat::Entry* datFileEntry);

protected:
    virtual void _initialize() override;

    /**
     * Called when initializing file.
     */
    virtual void _parseText(std::istream& istr) = 0;
};

}
}


#endif //FALLTERGEIST_TXT_BASEFILE_H
