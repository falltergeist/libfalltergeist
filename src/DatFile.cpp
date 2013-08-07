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

#include "../src/DatFile.h"
#include "../src/DatFileItem.h"
#include <iostream>
#include <string>
#include <algorithm>

namespace libfalltergeist
{

/**
 * Creates empty DAT file with no filename
 * @brief DatFile::DatFile
 */
DatFile::DatFile()
{
    _filename = 0;
    _items = 0;
}

/**
 * Opens selected DAT file
 * @brief DatFile::DatFile
 */
DatFile::DatFile(char * filename)
{
    _filename = 0;
    setFilename(filename);
    _items = 0;
}

/**
 * Destroys DAT file object 
 */
DatFile::~DatFile()
{
    while (!_items->empty())
    {
        delete _items->back();
        _items->pop_back();
    }
    delete _items;
    delete [] _filename;
}

char * DatFile::filename()
{
    return _filename;
}

void DatFile::setFilename(char * filename)
{
    delete [] _filename;
    _filename = new char[strlen(filename) + 1]();
    memcpy(_filename, filename, strlen(filename));
}


/**
 * Returns DatFile entries
 * @brief DatFile::getItems
 * @return
 */
std::vector<DatFileItem *> * DatFile::items()
{
    if (_items != 0) return _items;

    _items = new std::vector<DatFileItem *>;

    std::ifstream * stream = new std::ifstream();
    stream->open(filename(), std::ios_base::binary);
    if (!stream->is_open()) throw;

    // reading file size from dat file
    stream->seekg(4, std::ios::end);
    unsigned int datFileSize;
    *stream >> datFileSize;

    std::cout << "DatFileSize: " << datFileSize << std::endl;
    datFileSize = _littleEndian(datFileSize);
    std::cout << "DatFileSize: " << datFileSize << std::endl;


//        // reading size of files tree
//        setPosition(size() - 8);
//        unsigned int filesTreeSize = readUint32();
//
//        // reading total number of items in dat file
//        setPosition(size() - filesTreeSize - 8);
//        unsigned int filesTotalNumber = readUint32();
//
//        //reading files data one by one
//        for (unsigned int i = 0; i != filesTotalNumber; ++i)
//        {
//            DatFileItem * item = new DatFileItem(this);
//
//            //reading fileName
//            unsigned int filenameSize = readUint32();
//            char * filename = new char[filenameSize + 1]();
//            readBytes(filename, filenameSize);
//            item->setFilename(filename);
//            delete [] filename;
//
//            //reading compression flag
//            item->setCompressed(readUint8() == 1 ? true : false);
//
//            //reading unpacked size
//            item->setUnpackedSize(readUint32());
//
//            //reading packed size
//            item->setPackedSize(readUint32());
//
//            //reading data offset from dat file begining
//            item->setDataOffset(readUint32());
//
//            _items->push_back(item);
//      }
//        std::cout << "[OK]" << std::endl;
//        std::cout << "Items loaded: " << filesTotalNumber << std::endl;
    return _items;
}

unsigned int DatFile::_littleEndian(unsigned int data)
{
    unsigned char * memp = reinterpret_cast<unsigned char *>(&data);
    std::reverse(memp, memp + sizeof(data));
    return data;
    //return ( data[3] << 24) | (data[2] << 16) | ( data[1] << 8) | data[0];
}

int DatFile::_littleEndian(int data)
{
    return (int) _littleEndian((unsigned int) data);
}

unsigned short DatFile::_littleEndian(unsigned short data)
{
    unsigned char * memp = reinterpret_cast<unsigned char *>(&data);
    std::reverse(memp, memp + sizeof(data));
    return data;
}

short DatFile::_littleEndian(short data)
{
    return (short) _littleEndian((unsigned short) data);
}

char * DatFile::getItemData(unsigned int offset, unsigned int size)
{
    char * data = new char[size];

    std::ifstream * stream = new std::ifstream();
    stream->open(filename(), std::ios_base::binary);
    if (!stream->is_open()) throw;
    stream->seekg(offset, std::ios::beg);
    stream->readsome(data, size);
    delete stream;
}

}
