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

#ifndef LIBFALLTERGEIST_AAFFILETYPE_H
#define LIBFALLTERGEIST_AAFFILETYPE_H

// C++ standard includes
#include <vector>
#include <fstream>

// libfalltergeist includes
#include "../src/DatFileItem.h"

// Third party includes

namespace libfalltergeist
{
class AafGlyph;

class AafFileType : public DatFileItem
{
protected:
    std::vector<AafGlyph*> _glyphs;
    unsigned int _signature;
    unsigned short _maximumHeight = 0;
    unsigned short _maximumWidth = 0;
    unsigned short _horizontalGap = 0;
    unsigned short _spaceWidth = 0;
    unsigned short _verticalGap = 0;
    virtual void _initialize();
    unsigned int* _rgba = 0;
public:
    AafFileType(DatFileEntry* datFileEntry);
    AafFileType(std::ifstream* stream);
    ~AafFileType();

    unsigned* rgba();

    std::vector<AafGlyph*>* glyphs();

    unsigned short maximumHeight();
    unsigned short maximumWidth();
    unsigned short horizontalGap();
    unsigned short verticalGap();
    unsigned short spaceWidth();
};

}
#endif // LIBFALLTERGEIST_AAFFILETYPE_H
