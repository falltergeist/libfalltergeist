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
#include "../src/MsgFileType.h"
#include "../src/BioFileType.h"
#include "../src/GcdFileType.h"
#include <algorithm>
#include <zlib.h>
#include <iostream>

namespace libfalltergeist
{

DatFileItem::DatFileItem(DatFile * datFile): _datFile(datFile)
{
    _asAaf = 0;
    _asBio = 0;
    _asFrm = 0;
    _asGcd = 0;
    _asLst = 0;
    _asMsg = 0;
    _asPal = 0;
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
    delete _asAaf;
    delete _asBio;
    delete _asFrm;
    delete _asGcd;
    delete _asLst;
    delete _asMsg;
    delete _asPal;
    delete [] _data;
    delete [] _filename;
}


/**
 * Returns DatFile object
 * @brief DatFileItem::getDatFile
 * @return
 */
DatFile * DatFileItem::datFile()
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
 * Returns filename with path
 * @brief DatFileItem::getFilename
 */
char * DatFileItem::filename()
{
    return _filename;
}

unsigned int DatFileItem::dataOffset()
{
    return _dataOffset;
}

void DatFileItem::setDataOffset(unsigned int offset)
{
    _dataOffset = offset;
}

unsigned int DatFileItem::unpackedSize()
{
    return _unpackedSize;
}

void DatFileItem::setUnpackedSize(unsigned int size)
{
    _unpackedSize = size;
}

unsigned int DatFileItem::packedSize()
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

bool DatFileItem::compressed()
{
    return _compressed;
}

char * DatFileItem::getData()
{
    return (char * )_data;
}

unsigned int DatFileItem::readUint32()
{
    open();
    unsigned int pos = this->position();
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
    unsigned int pos = this->position();
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
    unsigned int pos = this->position();
    unsigned char value = _data[pos];
    setPosition(pos + 1);
    return value;
}

char DatFileItem::readInt8()
{
    return (char) readUint8();
}

unsigned int DatFileItem::size()
{
    return unpackedSize();
}

void DatFileItem::setPosition(unsigned int position)
{
    _position = position;
}

unsigned int DatFileItem::position()
{
    return _position;
}

void DatFileItem::open()
{
    if (isOpened()) return;

    _data = new unsigned char[unpackedSize()]();
    _datFile->setPosition(dataOffset());

    if (compressed())
    {
        char * packedData = new char[packedSize()]();
        _datFile->readBytes(packedData, packedSize());

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
    else
    {
        // just copying from dat file
        _datFile->readBytes((char *)_data, unpackedSize());
    }
    _opened = true;
}

void DatFileItem::skipBytes(unsigned int numberOfBytes)
{
    setPosition(position() + numberOfBytes);
}

void DatFileItem::readBytes(char * destination, unsigned int numberOfBytes)
{
    open();
    memcpy(destination, _data + position(), numberOfBytes);
    setPosition(position() + numberOfBytes);
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
    if (_asFrm) return _asFrm;
    _asFrm = new FrmFileType(this);
    return _asFrm;
}

PalFileType * DatFileItem::asPalFileType()
{
    if (_asPal) return _asPal;
    _asPal = new PalFileType(this);
    return _asPal;
}

LstFileType * DatFileItem::asLstFileType()
{
    if (_asLst) return _asLst;
    _asLst = new LstFileType(this);
    return _asLst;
}

AafFileType * DatFileItem::asAafFileType()
{
    if (_asAaf) return _asAaf;
    _asAaf = new AafFileType(this);
    return _asAaf;
}

MsgFileType * DatFileItem::asMsgFileType()
{
    if (_asMsg) return _asMsg;
    _asMsg = new MsgFileType(this);
    return _asMsg;
}

BioFileType * DatFileItem::asBioFileType()
{
    if (_asBio) return _asBio;
    _asBio = new BioFileType(this);
    return _asBio;
}

GcdFileType * DatFileItem::asGcdFileType()
{
    if (_asGcd) return _asGcd;
    _asGcd = new GcdFileType(this);
    return _asGcd;
}

}
