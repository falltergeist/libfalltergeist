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
    std::vector<AafGlyph *> * getGlyphs();
    unsigned short getMaximumHeight();
    unsigned short getHorizontalGap();
    unsigned short getVerticalGap();
    unsigned short getSpaceWidth();
    void setMaximumHeight(unsigned short height);
    void setHorizontalGap(unsigned short gap);
    void setVerticalGap(unsigned short gap);
    void setSpaceWidth(unsigned short width);
};

}
#endif // LIBFALLTERGEIST_AAFFILETYPE_H
