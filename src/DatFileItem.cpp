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
#include <zlib.h>
#include <iostream>

namespace libfalltergeist
{

DatFileItem::DatFileItem(DatFile * datFile): _datFile(datFile), _data(0), _filename(0)
{
}

DatFileItem::~DatFileItem()
{
    delete [] _data;
    delete [] _filename;
}


/**
 * Returns DatFile object
 */
DatFile * DatFileItem::datFile()
{
    return _datFile;
}

/**
 * Sets filename with path
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
 */
char * DatFileItem::filename()
{
    return _filename;
}

/**
 * Returns data offset in DAT file
 */
unsigned int DatFileItem::dataOffset()
{
    return _dataOffset;
}

/**
 * Sets data offset in DAT file
 */
void DatFileItem::setDataOffset(unsigned int offset)
{
    _dataOffset = offset;
}

/**
 * Returns unpacked file size in bytes
 */
unsigned int DatFileItem::unpackedSize()
{
    return _unpackedSize;
}

/**
 * Sets unpacked file size in bytes
 */
void DatFileItem::setUnpackedSize(unsigned int size)
{
    _unpackedSize = size;
}

/**
 * Returns packed file size in bytes
 */
unsigned int DatFileItem::packedSize()
{
    return _packedSize;
}

/**
 * Sets packed file size in bytes
 */
void DatFileItem::setPackedSize(unsigned int size)
{
    _packedSize = size;
}

/**
 * Returns if file is compressed
 */
bool DatFileItem::compressed()
{
    return _compressed;
}

/**
 * Sets if file is compressed
 */
void DatFileItem::setCompressed(bool compressed)
{
    _compressed = compressed;
}

/**
 * Returns pointer to file data
 */
char * DatFileItem::data()
{
    if (_data != 0) return _data;

    // If file is not compressed
    if (!compressed())
    {
        _data = datFile()->getItemData(dataOffset(), packedSize());
        return _data;
    }

    char * packedData = datFile()->getItemData(dataOffset(), packedSize());
    _data = new char[unpackedSize()];

    // unpacking
    z_stream zStream;
    zStream.total_in  = zStream.avail_in  = packedSize();
    zStream.avail_in = packedSize();
    zStream.next_in  = (unsigned char *) packedData;
    zStream.total_out = zStream.avail_out = unpackedSize();
    zStream.next_out = (unsigned char *) _data;
    zStream.zalloc = Z_NULL;
    zStream.zfree = Z_NULL;
    zStream.opaque = Z_NULL;
    inflateInit( &zStream );            // zlib function
    inflate( &zStream, Z_FINISH );      // zlib function
    inflateEnd( &zStream );             // zlib function

     delete [] packedData;
}

}
