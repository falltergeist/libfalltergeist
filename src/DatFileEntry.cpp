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
#include <algorithm>

// libfalltergeist includes
#include "../src/DatFileEntry.h"
#include "../src/DatFile.h"

// Third party includes

namespace libfalltergeist
{

DatFileEntry::DatFileEntry(DatFile* datFile)
{
    _datFile = datFile;
}

DatFileEntry::~DatFileEntry()
{
}

std::string DatFileEntry::filename() const
{
    return _filename;
}

void DatFileEntry::setFilename(std::string value)
{
    std::replace(value.begin(),value.end(),'\\','/');
    std::transform(value.begin(),value.end(),value.begin(), ::tolower);
    _filename = value;
}

unsigned int DatFileEntry::packedSize() const
{
    return _packedSize;
}

void DatFileEntry::setPackedSize(unsigned int value)
{
    _packedSize = value;
}

unsigned int DatFileEntry::unpackedSize() const
{
    return _unpackedSize;
}

void DatFileEntry::setUnpackedSize(unsigned int value)
{
    _unpackedSize = value;
}

unsigned int DatFileEntry::dataOffset() const
{
    return _dataOffset;
}

void DatFileEntry::setDataOffset(unsigned int value)
{
    _dataOffset = value;
}

bool DatFileEntry::compressed() const
{
    return _compressed;
}

void DatFileEntry::setCompressed(bool value)
{
    _compressed = value;
}

DatFile* DatFileEntry::datFile() const
{
    return _datFile;
}

}
