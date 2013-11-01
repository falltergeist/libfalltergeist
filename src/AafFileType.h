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
    unsigned short _maximumHeight;
    unsigned short _horizontalGap;
    unsigned short _spaceWidth;
    unsigned short _verticalGap;
    virtual void _initialize();
public:
    AafFileType(DatFileEntry* datFileEntry);
    AafFileType(std::ifstream* stream);
    ~AafFileType();

    std::vector<AafGlyph*>* glyphs();

    AafFileType* setMaximumHeight(unsigned short height);
    unsigned short maximumHeight();

    AafFileType* setHorizontalGap(unsigned short gap);
    unsigned short horizontalGap();

    AafFileType* setVerticalGap(unsigned short gap);
    unsigned short verticalGap();

    AafFileType* setSpaceWidth(unsigned short width);
    unsigned short spaceWidth();
};

}
#endif // LIBFALLTERGEIST_AAFFILETYPE_H
