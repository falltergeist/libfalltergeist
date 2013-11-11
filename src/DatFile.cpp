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
#include <algorithm>

// libfalltergeist includes
#include "../src/DatFile.h"
#include "../src/DatFileItem.h"
#include "../src/DatFileEntry.h"
#include "../src/Exception.h"
#include "../src/AafFileType.h"
#include "../src/BioFileType.h"
#include "../src/FonFileType.h"
#include "../src/FrmFileType.h"
#include "../src/GamFileType.h"
#include "../src/GcdFileType.h"
#include "../src/IntFileType.h"
#include "../src/MapFileType.h"
#include "../src/MsgFileType.h"
#include "../src/LstFileType.h"
#include "../src/PalFileType.h"
#include "../src/ProFileType.h"
#include "../src/RixFileType.h"

// Third party includes

namespace libfalltergeist
{

DatFile::DatFile()
{
}

DatFile::DatFile(std::string filename)
{
    setFilename(filename);
    _initialize();
}

DatFile::~DatFile()
{
    delete _items;
    delete _stream;
}

std::string DatFile::filename()
{
    return _filename;
}

DatFile* DatFile::setFilename(std::string filename)
{
    _filename = filename;
    return this;
}

void DatFile::_initialize()
{
    if (_initialized) return;
    _initialized = true;

    _stream = new std::ifstream();
    _stream->open(filename(), std::ios_base::binary);
    if (!_stream->is_open())
    {
        throw Exception("DatFile::_initialize() - can't open stream: " + filename());
    }
}

DatFile* DatFile::setPosition(unsigned int position)
{
    _stream->seekg(position, std::ios::beg);
    return this;
}

unsigned int DatFile::position()
{
    return _stream->tellg();
}

unsigned int DatFile::size(void)
{
    auto oldPosition = _stream->tellg();
    _stream->seekg(0,std::ios::end);
    auto currentPosition = _stream->tellg();
    _stream->seekg(oldPosition, std::ios::beg);
    return currentPosition;
}

DatFile* DatFile::skipBytes(unsigned int numberOfBytes)
{
    setPosition(position() + numberOfBytes);
    return this;
}

DatFile* DatFile::readBytes(char * destination, unsigned int numberOfBytes)
{
    unsigned int position = this->position();
    _stream->read(destination, numberOfBytes);
    setPosition(position + numberOfBytes);
    return this;
}

std::vector<DatFileItem *> * DatFile::items()
{
    // if items are not fetched yet
    if (_items == 0)
    {
        unsigned int oldPos = position();
        _items = new std::vector<DatFileItem *>;

        unsigned int datFileSize;
        unsigned int filesTreeSize;
        unsigned int filesTotalNumber;

        // reading data size from dat file
        setPosition(size() - 4);
        *this >> datFileSize;
        if (datFileSize != size())
        {
            throw Exception("DatFile::items() - wrong file size");
        }
        // reading size of files tree
        setPosition(size() - 8);
        *this >> filesTreeSize;

        // reading total number of items in dat file
        setPosition(size() - filesTreeSize - 8);
        *this >> filesTotalNumber;

        //reading files data one by one
        for (unsigned int i = 0; i != filesTotalNumber; ++i)
        {
            DatFileEntry * entry = new DatFileEntry(this);

            *this >> *entry;

            std::string extension = entry->filename().substr(entry->filename().length() - 3, 3);

            DatFileItem * item;
                 if (extension == "aaf") item = new AafFileType(entry);
            else if (extension == "bio") item = new BioFileType(entry);
            else if (extension == "fon") item = new FonFileType(entry);
            else if (extension == "frm") item = new FrmFileType(entry);
            else if (extension == "gam") item = new GamFileType(entry);
            else if (extension == "gcd") item = new GcdFileType(entry);
            else if (extension == "int") item = new IntFileType(entry);
            else if (extension == "lst") item = new LstFileType(entry);
            else if (extension == "map") item = new MapFileType(entry);
            else if (extension == "msg") item = new MsgFileType(entry);
            else if (extension == "pal") item = new PalFileType(entry);
            else if (extension == "pro") item = new ProFileType(entry);
            else if (extension == "rix") item = new RixFileType(entry);
            else item = new DatFileItem(entry);

            _items->push_back(item);
        }
        setPosition(oldPos);
    }
    return _items;
}

DatFileItem * DatFile::item(const std::string filename)
{
    std::string name(filename);
    // Replace slashes and transform to lower case
    std::replace(name.begin(),name.end(),'\\','/');
    std::transform(name.begin(),name.end(),name.begin(), ::tolower);
    std::vector<DatFileItem *>::iterator it;


    for (it = this->items()->begin(); it != this->items()->end(); ++it)
    {
        //std::cout << (*it)->filename() << std::endl;
        if (name.compare((*it)->filename()) == 0)
        {
            return *it;
        }
    }
    return 0;
}

DatFile& DatFile::operator>>(int &value)
{
    readBytes(reinterpret_cast<char *>(&value), sizeof(value));
    return *this;
}

DatFile& DatFile::operator>>(unsigned int &value)
{
    return *this >> (int&) value;
}

DatFile& DatFile::operator>>(short &value)
{
    readBytes(reinterpret_cast<char *>(&value), sizeof(value));
    return *this;
}

DatFile& DatFile::operator>>(unsigned short &value)
{
    return *this >> (short&) value;
}

DatFile& DatFile::operator>>(char &value)
{
    readBytes(reinterpret_cast<char *>(&value), sizeof(value));
    return *this;
}

DatFile& DatFile::operator>>(unsigned char &value)
{
    return *this >> (char&) value;
}

DatFile& DatFile::operator>>(DatFileEntry& entry)
{
    unsigned int filenameSize;
    unsigned char compressed;
    unsigned int unpackedSize;
    unsigned int packedSize;
    unsigned int dataOffset;

    *this >> filenameSize;

    std::string filename;
    filename.resize(filenameSize);
    readBytes(&filename[0], filenameSize);
    entry.setFilename(filename);

    *this >> compressed >> unpackedSize >> packedSize >> dataOffset;

    entry.setCompressed((bool) compressed);
    entry.setUnpackedSize(unpackedSize);
    entry.setPackedSize(packedSize);
    entry.setDataOffset(dataOffset);

    return *this;
}

}
