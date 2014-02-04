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

// C++ standard inludes

// libfalltergeist includes
#include "../src/AafFileType.h"
#include "../src/AafGlyph.h"

// Third party includes

namespace libfalltergeist
{

AafFileType::AafFileType(DatFileEntry* datFileEntry): DatFileItem(datFileEntry)
{
}

AafFileType::AafFileType(std::ifstream* stream): DatFileItem(stream)
{
}

AafFileType::~AafFileType()
{
    while(!_glyphs.empty())
    {
        delete _glyphs.back();
        _glyphs.pop_back();
    }
}

void AafFileType::_initialize()
{
    if (_initialized) return;
    DatFileItem::_initialize();
    DatFileItem::setPosition(0);

    *this >> _signature >> _maximumHeight >> _horizontalGap >> _spaceWidth >> _verticalGap;

    // glyphs descriptions
    std::vector<unsigned int> dataOffsets(256);
    for (auto i = 0; i != 256; ++i)
    {
        unsigned short width, height;
        *this >> width >> height >> dataOffsets.at(i);
        _glyphs.push_back(new AafGlyph(width, height));
    }

    // glyphs data
    for (auto i = 0; i != 256; ++i)
    {
        setPosition(0x080C + dataOffsets.at(i));
        auto glyph = _glyphs.at(i);
        for (auto j = 0; j != glyph->width()*glyph->height(); ++j)
        {
            unsigned char byte;
            *this >> byte;
            glyph->data()->push_back(byte);
        }
    }
}

std::vector<AafGlyph*>* AafFileType::glyphs()
{
    _initialize();
    return &_glyphs;
}

unsigned short AafFileType::horizontalGap()
{
    _initialize();
    return _horizontalGap;
}

AafFileType* AafFileType::setHorizontalGap(unsigned short gap)
{
    _horizontalGap = gap;
    return this;
}

unsigned short AafFileType::maximumHeight()
{
    _initialize();
    return _maximumHeight;
}

AafFileType* AafFileType::setMaximumHeight(unsigned short height)
{
    _maximumHeight = height;
    return this;
}

unsigned short AafFileType::spaceWidth()
{
    _initialize();
    return _spaceWidth;
}

AafFileType* AafFileType::setSpaceWidth(unsigned short width)
{
    _spaceWidth = width;
    return this;
}

unsigned short AafFileType::verticalGap()
{
    _initialize();
    return _verticalGap;
}

AafFileType* AafFileType::setVerticalGap(unsigned short gap)
{
    _verticalGap = gap;
    return this;
}

}
