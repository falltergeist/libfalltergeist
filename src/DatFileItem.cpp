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

#include <string.h>
#include "../src/DatFileItem.h"
#include "../src/DatFile.h"
#include <algorithm>

namespace libfalltergeist
{

DatFileItem::DatFileItem(DatFile * datFile): _datFile(datFile)
{
    data = 0;
    _filename = 0;
    _dataOffset = 0;
    _unpackedSize = 0;
    _packedSize = 0;
    _isCompressed = false;
}

DatFileItem::~DatFileItem()
{
    delete [] data;
    delete [] _filename;
}

/**
 * Sets filename with path
 * @brief DatFileItem::setFilename
 * @param filename
 */
void DatFileItem::setFilename(char * filename)
{
    if (_filename != 0) delete [] _filename;

    // convert to lowercase and replace slashes
    std::string fname(filename);
    std::replace(fname.begin(),fname.end(),'\\','/');
    std::transform(fname.begin(),fname.end(),fname.begin(), ::tolower);

    _filename = new char[strlen(fname.c_str()) + 1]();
    strcpy(_filename, fname.c_str());
}

/**
 * Returns filename with path
 * @brief DatFileItem::getFilename
 */
char * DatFileItem::getFilename()
{
    return _filename;
}

unsigned int DatFileItem::getDataOffset()
{
    return _dataOffset;
}

void DatFileItem::setDataOffset(unsigned int offset)
{
    _dataOffset = offset;
}

unsigned int DatFileItem::getUnpackedSize()
{
    return _unpackedSize;
}

void DatFileItem::setUnpackedSize(unsigned int size)
{
    _unpackedSize = size;
}

unsigned int DatFileItem::getPackedSize()
{
    return _packedSize;
}

void DatFileItem::setPackedSize(unsigned int size)
{
    _packedSize = size;
}

void DatFileItem::setIsCompressed(bool compressed)
{
    _isCompressed = compressed;
}

bool DatFileItem::isCompressed()
{
    return _isCompressed;
}

}
