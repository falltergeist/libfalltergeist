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

// C++ standard includes

// libfalltergeist includes
#include "../src/PalFileType.h"
#include "../src/PalColor.h"

// Third party includes

namespace libfalltergeist
{

PalFileType::PalFileType(DatFileEntry* datFileEntry) : DatFileItem(datFileEntry)
{
}

PalFileType::PalFileType(std::ifstream* stream) : DatFileItem(stream)
{
}

PalFileType::~PalFileType()
{
}

void PalFileType::_initialize()
{
    if (_initialized) return;
    DatFileItem::_initialize();
    DatFileItem::setPosition(3);

    _colors.push_back(new PalColor(0, 0, 9, 0)); // zero color (transparent)

    for (unsigned int i = 1; i != 256; ++i)
    {
        unsigned char r, g, b;
        *this >> r >> g >> b;
        _colors.push_back(new PalColor(r, g, b));
    }
}

std::vector<PalColor*>* PalFileType::colors()
{
    _initialize();
    return &_colors;
}

PalColor* PalFileType::color(unsigned char index)
{
    _initialize();
    return _colors.at(index);
}

}
