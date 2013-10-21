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
#include "../src/DatFileEntry.h"
#include "../src/DatFile.h"

// Third party includes

namespace libfalltergeist
{

DatFileEntry::DatFileEntry(DatFile * datFile)
{
    _datFile = datFile;
}

DatFileEntry::~DatFileEntry()
{
}

std::string DatFileEntry::filename()
{
    return _filename;
}

void DatFileEntry::setFilename(std::string value)
{
    _filename = value;
}

unsigned int DatFileEntry::packedSize()
{
    return _packedSize;
}

void DatFileEntry::setPackedSize(unsigned int value)
{
    _packedSize = value;
}

unsigned int DatFileEntry::unpackedSize()
{
    return _unpackedSize;
}

void DatFileEntry::setUnpackedSize(unsigned int value)
{
    _unpackedSize = value;
}

unsigned int DatFileEntry::dataOffset()
{
    return _dataOffset;
}

void DatFileEntry::setDataOffset(unsigned int value)
{
    _dataOffset = value;
}

bool DatFileEntry::compressed()
{
    return _compressed;
}

void DatFileEntry::setCompressed(bool value)
{
    _compressed = value;
}

DatFile * DatFileEntry::datFile()
{
    return _datFile;
}

}
