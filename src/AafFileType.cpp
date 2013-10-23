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

// C++ standard inludes

// libfalltergeist includes
#include "../src/AafFileType.h"
#include "../src/AafGlyph.h"
#include "../src/DatFileItem.h"
#include "../src/DatFileEntry.h"

// Third party includes

namespace libfalltergeist
{

AafFileType::AafFileType(DatFileEntry * datFileEntry): DatFileItem(datFileEntry)
{
    _glyphs = 0;
}

AafFileType::AafFileType(std::ifstream * stream): DatFileItem(stream)
{
    _glyphs = 0;
}

AafFileType::~AafFileType()
{
    if (_glyphs != 0)
    {
        while(!_glyphs->empty())
        {
            delete _glyphs->back();
            _glyphs->pop_back();
        }
        delete _glyphs;
    }

}

void AafFileType::_initialize()
{
    if (_initialized) return;
    DatFileItem::_initialize();
    DatFileItem::setPosition(0);

    _glyphs = new std::vector<AafGlyph *>;


    *this >> _signature >> _maximumHeight >> _horizontalGap >> _spaceWidth >> _verticalGap;

    std::vector<unsigned int> * dataOffsets = new std::vector<unsigned int>(256);

    // glyphs descriptions
    for (unsigned int i = 0; i != 256; ++i)
    {
        unsigned short width, height;
        *this >> width >> height >> dataOffsets->at(i);
        _glyphs->push_back(new AafGlyph(width, height));
    }

    // glyphs data
    for (unsigned int i = 0; i != 256; ++i)
    {
        setPosition(0x080C + dataOffsets->at(i));
        for (int j = 0; j != _glyphs->at(i)->width()*_glyphs->at(i)->height(); ++j)
        {
            *this >> _glyphs->at(i)->data()->at(j);
        }
    }

    delete dataOffsets;
}

std::vector<AafGlyph *> * AafFileType::glyphs()
{
    _initialize();
    return _glyphs;
}

unsigned short AafFileType::horizontalGap()
{
    _initialize();
    return _horizontalGap;
}

void AafFileType::setHorizontalGap(unsigned short gap)
{
    _horizontalGap = gap;
}

unsigned short AafFileType::maximumHeight()
{
    _initialize();
    return _maximumHeight;
}

void AafFileType::setMaximumHeight(unsigned short height)
{
    _maximumHeight = height;
}

unsigned short AafFileType::spaceWidth()
{
    _initialize();
    return _spaceWidth;
}

void AafFileType::setSpaceWidth(unsigned short width)
{
    _spaceWidth = width;
}

unsigned short AafFileType::verticalGap()
{
    _initialize();
    return _verticalGap;
}

void AafFileType::setVerticalGap(unsigned short gap)
{
    _verticalGap = gap;
}

}
