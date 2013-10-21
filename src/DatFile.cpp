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
#include "../src/FrmFileType.h"
#include "../src/GcdFileType.h"
#include "../src/MsgFileType.h"
#include "../src/LstFileType.h"
#include "../src/PalFileType.h"
#include "../src/ProFileType.h"

// Third party includes

namespace libfalltergeist
{

DatFile::DatFile()
{
    _items = 0;
    _stream = 0;
}

DatFile::DatFile(std::string pathToFile)
{
    _items = 0;
    _stream = 0;
    open(pathToFile);
}

DatFile::~DatFile()
{
    delete _items;
    delete _stream;
}

std::string DatFile::pathToFile()
{
    return _pathToFile;
}

bool DatFile::open(std::string pathToFile)
{
    _pathToFile.clear();
    _pathToFile.append(pathToFile);

    _stream = new std::ifstream();
    _stream->open(_pathToFile.c_str(), std::ios_base::binary);
    if (_stream->is_open())
    {
        return true;
    }
    return false;
}

bool DatFile::isOpened()
{
    if (_stream && _stream->is_open())
    {
        return true;
    }
    return false;
}


void DatFile::setPosition(unsigned int position)
{
    _stream->seekg(position, std::ios::beg);
}

unsigned int DatFile::position()
{
    return _stream->tellg();
}

unsigned int DatFile::size(void)
{
    if (!_stream || !_stream->is_open()) return 0;
    unsigned int oldPosition = _stream->tellg();
    _stream->seekg(0,std::ios::end);
    unsigned int currentPosition = _stream->tellg();
    _stream->seekg(oldPosition, std::ios::beg);
    return currentPosition;
}

void DatFile::skipBytes(unsigned int numberOfBytes)
{
    setPosition(position() + numberOfBytes);
}

void DatFile::readBytes(char * destination, unsigned int numberOfBytes)
{
    unsigned int position = this->position();
    _stream->readsome(destination, numberOfBytes);
    setPosition(position + numberOfBytes);
}

std::vector<DatFileItem *> * DatFile::items()
{
    if (!isOpened()) return 0;


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
            else if (extension == "frm") item = new FrmFileType(entry);
            else if (extension == "gcd") item = new GcdFileType(entry);
            else if (extension == "lst") item = new LstFileType(entry);
            else if (extension == "msg") item = new MsgFileType(entry);
            else if (extension == "pal") item = new PalFileType(entry);
            else if (extension == "pro") item = new ProFileType(entry);
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

    char * filename = new char[filenameSize + 1]();
    readBytes(filename, filenameSize);
    entry.setFilename(filename);
    delete [] filename;

    *this >> compressed >> unpackedSize >> packedSize >> dataOffset;

    entry.setCompressed((bool) compressed);
    entry.setUnpackedSize(unpackedSize);
    entry.setPackedSize(packedSize);
    entry.setDataOffset(dataOffset);

    return *this;
}

}
