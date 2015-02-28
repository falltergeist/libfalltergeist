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
#include "../Dat/Entry.h"
#include "../Dat/File.h"

// Third party includes

namespace libfalltergeist
{
namespace Dat
{

Entry::Entry(File* datFile)
{
    _datFile = datFile;
}

Entry::~Entry()
{
}

std::string Entry::filename()
{
    return _filename;
}

void Entry::setFilename(std::string value)
{
    std::replace(value.begin(),value.end(),'\\','/');
    std::transform(value.begin(),value.end(),value.begin(), ::tolower);
    _filename = value;
}

uint32_t Entry::packedSize()
{
    return _packedSize;
}

void Entry::setPackedSize(uint32_t value)
{
    _packedSize = value;
}

uint32_t Entry::unpackedSize()
{
    return _unpackedSize;
}

void Entry::setUnpackedSize(uint32_t value)
{
    _unpackedSize = value;
}

uint32_t Entry::dataOffset()
{
    return _dataOffset;
}

void Entry::setDataOffset(uint32_t value)
{
    _dataOffset = value;
}

bool Entry::compressed()
{
    return _compressed;
}

void Entry::setCompressed(bool value)
{
    _compressed = value;
}

File* Entry::datFile()
{
    return _datFile;
}

}
}
