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
#include <iostream>

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
    delete [] _rgba;
}

void AafFileType::_initialize()
{
    if (_initialized) return;
    DatFileItem::_initialize();
    DatFileItem::setPosition(0);

    *this >> _signature >> _maximumHeight >> _horizontalGap >> _spaceWidth >> _verticalGap;

    // glyphs info
    for (auto i = 0; i != 256; ++i)
    {
        unsigned short width, height;
        unsigned int offset;
        *this >> width >> height >> offset;
        if (width > _maximumWidth) _maximumWidth = width;
        AafGlyph* glyph = new AafGlyph(width, height);
        glyph->setDataOffset(offset);
        _glyphs.push_back(glyph);
    }

    // glyphs data
    for (auto i = 0; i != 256; ++i)
    {
        //setPosition(0x080C + _glyphs.at(i)->dataOffset());
        //auto glyph = _glyphs.at(i);
        //for (auto j = 0; j != glyph->width()*glyph->height(); ++j)
        //{
            //unsigned char byte;
            //*this >> byte;
            //glyph->data()->push_back(byte);
        //}
    }
}

unsigned int* AafFileType::rgba()
{
    if (_rgba) return _rgba;
    _initialize();
    _rgba = new unsigned int[_maximumWidth * _maximumHeight * 256]();

    for (unsigned int i = 0; i != 256; ++i)
    {
        unsigned int glyphY = (i/16) * _maximumHeight;

        // Прижимаем глиф к низу
        glyphY += _maximumHeight - _glyphs.at(i)->height();

        unsigned int glyphX = (i%16) * _maximumWidth;
        std::cout << glyphX << " : " << glyphY << std::endl;

        setPosition(0x080C + _glyphs.at(i)->dataOffset());

        std::cout << _glyphs.at(i)->height() << std::endl;

        for (unsigned int y = 0; y != _glyphs.at(i)->height(); ++y)
        {
            for (unsigned int x = 0; x != _glyphs.at(i)->width(); ++x)
            {
                unsigned char byte;
                *this >> byte;

                std::cout << byte << std::endl;

                if (byte != 0)
                {
                    _rgba[(glyphY + y)*_maximumWidth*16  + glyphX + x] = 0x00FF00FF;
                }


            }
        }
    }




    return _rgba;
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

unsigned short AafFileType::maximumHeight()
{
    _initialize();
    return _maximumHeight;
}

unsigned short AafFileType::maximumWidth()
{
    _initialize();
    return _maximumWidth;
}

unsigned short AafFileType::spaceWidth()
{
    _initialize();
    return _spaceWidth;
}

unsigned short AafFileType::verticalGap()
{
    _initialize();
    return _verticalGap;
}

}
