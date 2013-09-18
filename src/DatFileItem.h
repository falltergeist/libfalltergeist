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

#ifndef LIBFALLTERGEIST_DATFILEITEM_H
#define LIBFALLTERGEIST_DATFILEITEM_H

#include <string>

namespace libfalltergeist
{
class AafFileType;
class BioFileType;
class DatFile;
class FrmFileType;
class GcdFileType;
class LstFileType;
class MsgFileType;
class PalFileType;

class DatFileItem
{
protected:
    AafFileType * _asAaf;
    BioFileType * _asBio;
    FrmFileType * _asFrm;
    GcdFileType * _asGcd;
    LstFileType * _asLst;
    MsgFileType * _asMsg;
    PalFileType * _asPal;

    DatFile * _datFile; // DAT file object
    std::string _filename; // filename with path (path/to/file.ext)
    unsigned int _dataOffset; // data offset in the DAT file
    unsigned int _unpackedSize; // unpacked data size
    unsigned int _packedSize; // packed data size
    bool _compressed; // is packed?
    unsigned char * _data;
    unsigned int _position;
    bool _opened;
public:

    DatFileItem(DatFile * datFile);
    ~DatFileItem();

    DatFile * datFile();

    void setFilename(const std::string filename);
    std::string filename();

    void setDataOffset(unsigned int offset);
    unsigned int dataOffset();

    void setUnpackedSize(unsigned int size);
    unsigned int unpackedSize();

    void setPackedSize(unsigned int size);
    unsigned int packedSize();

    void setCompressed(bool compressed);
    bool compressed();

    unsigned int size();

    void setPosition(unsigned int position);
    unsigned int position();

    void setData(char * data);
    char * getData();

    unsigned int readUint32();
    int readInt32();
    unsigned short readUint16();
    short readInt16();
    unsigned char readUint8();
    char readInt8();
    void readBytes(char * destination, unsigned int numberOfBytes);
    void skipBytes(unsigned int numberOfBytes);
    void open();
    bool isOpened();
    void isOpened(bool val);
    void close();

    FrmFileType * asFrmFileType();
    PalFileType * asPalFileType();
    LstFileType * asLstFileType();
    AafFileType * asAafFileType();
    MsgFileType * asMsgFileType();
    BioFileType * asBioFileType();
    GcdFileType * asGcdFileType();

};

}
#endif //LIBFALLTERGEIST_DATFILEITEM_H
