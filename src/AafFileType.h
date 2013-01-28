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

#include <vector>

namespace libfalltergeist
{
class DatFileItem;
class AafGlyph;

class AafFileType
{
protected:
    DatFileItem * _datFileItem;
    std::vector<AafGlyph *> * _glyphs;
    unsigned short _maximumHeight;
    unsigned short _horizontalGap;
    unsigned short _spaceWidth;
    unsigned short _verticalGap;
public:
    AafFileType(DatFileItem * datFileItem);
    ~AafFileType();

    void open();

    DatFileItem * datFileItem();
    DatFileItem * getDatFileItem();

    std::vector<AafGlyph *> * glyphs();
    std::vector<AafGlyph *> * getGlyphs();

    void setMaximumHeight(unsigned short height);
    unsigned short maximumHeight();
    unsigned short getMaximumHeight();

    void setHorizontalGap(unsigned short gap);
    unsigned short horizontalGap();
    unsigned short getHorizontalGap();

    void setVerticalGap(unsigned short gap);
    unsigned short verticalGap();
    unsigned short getVerticalGap();

    void setSpaceWidth(unsigned short width);
    unsigned short spaceWidth();
    unsigned short getSpaceWidth();
};

}
#endif // LIBFALLTERGEIST_AAFFILETYPE_H
