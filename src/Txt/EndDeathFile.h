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

#ifndef FALLTERGEIST_TXT_ENDDEATHFILE_H
#define FALLTERGEIST_TXT_ENDDEATHFILE_H

// C++ standard includes
#include <list>

// Libfalltergeist includes
#include "../Txt/BaseFile.h"

// Third party includes


namespace libfalltergeist
{
namespace Txt
{

struct EndDeath
{
    int globalVar = -1;
    int minValue = 0;
    int worldAreaKnown = -1;
    int worldAreaNotKnown = -1;
    int minLevel = 0;
    unsigned char chance = 0;
    std::string narratorFile;
};

class EndDeathFile : public BaseFile
{

public:
    EndDeathFile(std::ifstream* stream);
    EndDeathFile(Dat::Entry* datFileEntry);

    const std::list<EndDeath>& items() const;

protected:
    virtual void _parseText(std::istream& istr) override;

    std::list<EndDeath> _items;
};

}
}


#endif //FALLTERGEIST_TXT_ENDDEATHFILE_H
