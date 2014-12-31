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

// C++ standard includes

// libfalltergeist includes
#include "../src/BioFileType.h"

// Third party includes

namespace libfalltergeist
{

BioFileType::BioFileType(std::shared_ptr<DatFileEntry> datFileEntry) : DatFileItem(datFileEntry)
{
}

BioFileType::BioFileType(std::ifstream* stream) : DatFileItem(stream)
{
}

BioFileType::~BioFileType()
{
}

void BioFileType::_initialize()
{
    if (_initialized) return;
    DatFileItem::_initialize();
    DatFileItem::setPosition(0);

    for (unsigned int i = 0; i != this->size(); ++i)
    {
        unsigned char ch;
        *this >> ch;
        _text += ch;
    }
}

std::string BioFileType::text()
{
    _initialize();
    return _text;
}

}
