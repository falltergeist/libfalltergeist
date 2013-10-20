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

// Third party includes

namespace libfalltergeist
{

AafFileType::AafFileType(DatFileItem * datFileItem): _datFileItem(datFileItem)
{
    _glyphs = 0;
    open();
}

AafFileType::~AafFileType()
{
    while(!_glyphs->empty())
    {
        delete _glyphs->back();
        _glyphs->pop_back();
    }
    delete _glyphs;
}

void AafFileType::open()
{
    DatFileItem &item = *datFileItem();

    _glyphs = new std::vector<AafGlyph *>;

    item.setPosition(0);

    item >> _signature; // "AAFF" Signature

    item >> _maximumHeight >> _horizontalGap >> _spaceWidth >> _verticalGap;

    std::vector<unsigned int> * dataOffsets = new std::vector<unsigned int>(256);

    // glyphs descriptions
    for (unsigned int i = 0; i != 256; ++i)
    {
        unsigned short width, height;
        item >> width
             >> height
             >> dataOffsets->at(i);
        _glyphs->push_back(new AafGlyph(width, height));
    }

    // glyphs data
    for (unsigned int i = 0; i != 256; ++i)
    {
        item.setPosition(0x080C + dataOffsets->at(i));
        for (unsigned int j = 0; j != _glyphs->at(i)->width()*_glyphs->at(i)->height(); ++j)
        {
            item >> _glyphs->at(i)->data()->at(j);
        }
    }

    delete dataOffsets;
}

DatFileItem * AafFileType::datFileItem()
{
    return _datFileItem;
}

std::vector<AafGlyph *> * AafFileType::glyphs()
{
    return _glyphs;
}

unsigned short AafFileType::horizontalGap()
{
    return _horizontalGap;
}

void AafFileType::setHorizontalGap(unsigned short gap)
{
    _horizontalGap = gap;
}

unsigned short AafFileType::maximumHeight()
{
    return _maximumHeight;
}

void AafFileType::setMaximumHeight(unsigned short height)
{
    _maximumHeight = height;
}

unsigned short AafFileType::spaceWidth()
{
    return _spaceWidth;
}

void AafFileType::setSpaceWidth(unsigned short width)
{
    _spaceWidth = width;
}

unsigned short AafFileType::verticalGap()
{
    return _verticalGap;
}

void AafFileType::setVerticalGap(unsigned short gap)
{
    _verticalGap = gap;
}

}
