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
#include <iostream>

// libfalltergeist includes
#include "../src/AcmFileType.h"

// Third party includes

namespace libfalltergeist
{

AcmFileType::AcmFileType(DatFileEntry* datFileEntry) : DatFileItem(datFileEntry)
{
}

AcmFileType::AcmFileType(std::ifstream* stream) : DatFileItem(stream)
{
}

AcmFileType::~AcmFileType()
{
}

void AcmFileType::_initialize()
{
    if (_initialized) return;
    DatFileItem::_initialize();
    DatFileItem::setPosition(0);
}

void AcmFileType::test()
{
    this->setEndianness(ENDIANNESS_LITTLE);

    // signature
    this->skipBytes(4);

    unsigned int samplesCounter;
    unsigned short chanels;
    unsigned short bitrate;
    unsigned short attributes;

    *this >> samplesCounter >> chanels >> bitrate >> attributes;

    std::cout << "Samples: " << samplesCounter << " Chanels: " << chanels << " Bitrate: " << bitrate << std::endl;
}


}
