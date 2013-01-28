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
#include "../src/FrmFileType.h"
#include "../src/PalFileType.h"
#include "../src/LstFileType.h"
#include "../src/AafFileType.h"
#include <algorithm>
#include <zlib.h>
#include <iostream>

namespace libfalltergeist
{

DatFileItem::DatFileItem(DatFile * datFile): _datFile(datFile)
{
    _data = 0;
    _filename = 0;
    _dataOffset = 0;
    _unpackedSize = 0;
    _packedSize = 0;
    _compressed = false;
    _opened = false;
    _position = 0;
}

DatFileItem::~DatFileItem()
{
    delete [] _data;
    delete [] _filename;
}

/**
 * Alias to DatFileItem::getDatFile
 * @brief DatFileItem::datFile
 * @return
 */
DatFile * DatFileItem::datFile()
{
    return getDatFile();
}

/**
 * Returns DatFile object
 * @brief DatFileItem::getDatFile
 * @return
 */
DatFile * DatFileItem::getDatFile()
{
    return _datFile;
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
 * Alias to DatFileItem::getFilename
 * @brief DatFileItem::filename
 * @return
 */
char * DatFileItem::filename()
{
    return getFilename();
}

/**
 * Returns filename with path
 * @brief DatFileItem::getFilename
 */
char * DatFileItem::getFilename()
{
    return _filename;
}

/**
 * Alias to DatFileItem::getDataOffset
 * @brief DatFileItem::dataOffset
 * @return
 */
unsigned int DatFileItem::dataOffset()
{
    return getDataOffset();
}


unsigned int DatFileItem::getDataOffset()
{
    return _dataOffset;
}

void DatFileItem::setDataOffset(unsigned int offset)
{
    _dataOffset = offset;
}

/**
 * Alias to DatFileItem::getUnpackedSize
 * @brief DatFileItem::unpackedSize
 * @return
 */
unsigned int DatFileItem::unpackedSize()
{
    return getUnpackedSize();
}

unsigned int DatFileItem::getUnpackedSize()
{
    return _unpackedSize;
}

void DatFileItem::setUnpackedSize(unsigned int size)
{
    _unpackedSize = size;
}

/**
 * Alias to DatFileItem::getPacketSize
 * @brief DatFileItem::packedSize
 * @return
 */
unsigned int DatFileItem::packedSize()
{
    return getPackedSize();
}

unsigned int DatFileItem::getPackedSize()
{
    return _packedSize;
}

void DatFileItem::setPackedSize(unsigned int size)
{
    _packedSize = size;
}

void DatFileItem::setCompressed(bool compressed)
{
    _compressed = compressed;
}

/**
 * Alias to DatFileItem::getCompressed
 * @brief DatFileItem::compressed
 * @return
 */
bool DatFileItem::compressed()
{
    return getCompressed();
}

bool DatFileItem::getCompressed()
{
    return _compressed;
}

unsigned int DatFileItem::readUint32()
{
    open();
    unsigned int pos = getPosition();
    unsigned int value = (_data[pos] << 24)| (_data[pos+ 1] << 16) | (_data[pos + 2] << 8) | _data[pos + 3];
    setPosition(pos + 4);
    return value;
}

int DatFileItem::readInt32()
{
    return (int) readUint32();
}

unsigned short DatFileItem::readUint16()
{
    open();
    unsigned int pos = getPosition();
    unsigned short value = (_data[pos] << 8) | _data[pos+ 1];
    setPosition(pos + 2);
    return value;
}

short DatFileItem::readInt16()
{
    return (short) readUint16();
}

unsigned char DatFileItem::readUint8()
{
    open();
    unsigned int pos = getPosition();
    unsigned char value = _data[pos];
    setPosition(pos + 1);
    return value;
}

char DatFileItem::readInt8()
{
    return (char) readUint8();
}

/**
 * Alias to DatFileItem::getSize
 * @brief DatFileItem::size
 * @return
 */
unsigned int DatFileItem::size()
{
    return getSize();
}

unsigned int DatFileItem::getSize()
{
    return getUnpackedSize();
}

void DatFileItem::setPosition(unsigned int position)
{
    _position = position;
}

/**
 * Alias to DatFileItem::getPosition
 * @brief DatFileItem::position
 * @return
 */
unsigned int DatFileItem::position()
{
    return getPosition();
}

unsigned int DatFileItem::getPosition()
{
    return _position;
}

void DatFileItem::open()
{
    if (isOpened()) return;

    _data = new unsigned char[getUnpackedSize()]();
    _datFile->setPosition(getDataOffset());

    if (getCompressed())
    {
        char * packedData = new char[getPackedSize()]();
        _datFile->readBytes(packedData, getPackedSize());

        // unpacking
        z_stream zStream;
        zStream.total_in  = zStream.avail_in  = getPackedSize();
        zStream.avail_in = getPackedSize();
        zStream.next_in  = (unsigned char *) packedData;
        zStream.total_out = zStream.avail_out = getUnpackedSize();
        zStream.next_out = (unsigned char *) _data;
        zStream.zalloc = Z_NULL;
        zStream.zfree = Z_NULL;
        zStream.opaque = Z_NULL;
        inflateInit( &zStream );            // zlib function
        inflate( &zStream, Z_FINISH );      // zlib function
        inflateEnd( &zStream );             // zlib function

        delete [] packedData;
    }
    else
    {
        // just copying from dat file
        _datFile->readBytes((char *)_data, getUnpackedSize());
    }
    _opened = true;
}

void DatFileItem::skipBytes(unsigned int numberOfBytes)
{
    setPosition(getPosition() + numberOfBytes);
}

void DatFileItem::readBytes(char * destination, unsigned int numberOfBytes)
{
    open();
    memcpy(destination, _data + getPosition(), numberOfBytes);
    setPosition(getPosition() + numberOfBytes);
}

bool DatFileItem::isOpened()
{
    return _opened;
}

void DatFileItem::close()
{
    if (!isOpened()) return;
    delete [] _data;
    _opened = false;
}

FrmFileType * DatFileItem::asFrmFileType()
{
    FrmFileType * frm = new FrmFileType(this);
    return frm;
}

PalFileType * DatFileItem::asPalFileType()
{
    PalFileType * pal = new PalFileType(this);
    return pal;
}

LstFileType * DatFileItem::asLstFileType()
{
    LstFileType * lst = new LstFileType(this);
    return lst;
}

AafFileType * DatFileItem::asAafFileType()
{
    AafFileType * aaf = new AafFileType(this);
    return aaf;
}

}
