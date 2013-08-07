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

unsigned int DatFile::size()
{
    std::ifstream * stream = new std::ifstream();
    stream->open(filename(), std::ios_base::binary);
    if (!stream->is_open())
    {
        std::cout << "Не удалось открыть DAT файл" << std::endl;
        throw;
    }

    // reading file size from dat file
    stream->seekg(0, std::ios::end);
    unsigned int size = stream->tellg();
    stream->close();
    delete stream;
    return size;
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
    if (!stream->is_open())
    {
        std::cout << "Не удалось открыть DAT файл" << std::endl;
        throw;
    }

    // reading file size from dat file
    stream->seekg(-4, std::ios::end);
    unsigned int datFileSize;
    stream->read(reinterpret_cast<char *>(&datFileSize), 4);

    // reading size of files tree
    stream->seekg(-8, std::ios::end);
    unsigned int filesTreeSize;
    stream->read(reinterpret_cast<char *>(&filesTreeSize), 4);

    // reading total number of items in dat file
    stream->seekg(datFileSize - filesTreeSize - 8, std::ios::beg);
    unsigned int filesTotalNumber;
    stream->read(reinterpret_cast<char *>(&filesTotalNumber), 4);

    //reading files data one by one
    for (unsigned int i = 0; i != filesTotalNumber; ++i)
    {
        DatFileItem * item = new DatFileItem(this);

        //reading fileName
        unsigned int filenameSize;
        stream->read(reinterpret_cast<char *>(&filenameSize), 4);
        char * filename = new char[filenameSize + 1]();
        stream->read(filename, filenameSize);
        item->setFilename(filename);
        delete [] filename;

        //reading compression flag
        unsigned char flag;
        stream->read(reinterpret_cast<char *>(&flag), 1);
        item->setCompressed(flag == 1 ? true : false);

        //reading unpacked size
        unsigned int unpackedSize;
        stream->read(reinterpret_cast<char *>(&unpackedSize), 4);
        item->setUnpackedSize(unpackedSize);

        //reading packed size
        unsigned int packedSize;
        stream->read(reinterpret_cast<char *>(&packedSize), 4);
        item->setPackedSize(packedSize);

        //reading data offset from dat file begining
        unsigned int dataOffset;
        stream->read(reinterpret_cast<char *>(&dataOffset), 4);
        item->setDataOffset(dataOffset);

        //std::cout << item->filename() << " " << (int) item->compressed() << " " << item->packedSize() << " " << item->unpackedSize() << std::endl;
        _items->push_back(item);

    }
    stream->close();
    delete stream;
    return _items;
}

DatFileItem * DatFile::item(char * filename)
{
    std::string needle(filename);
    std::replace(needle.begin(),needle.end(),'\\','/');
    std::transform(needle.begin(),needle.end(),needle.begin(), ::tolower);

    std::vector<DatFileItem *>::iterator it;
    for (it = items()->begin(); it != items()->end(); ++it)
    {
        if (strcmp(filename, (*it)->filename()) == 0)
        {
            return *it;
        }
    }
    return 0;
}



char * DatFile::getItemData(unsigned int offset, unsigned int size)
{
    char * data = new char[size];

    std::ifstream * stream = new std::ifstream();
    stream->open(filename(), std::ios_base::binary);
    if (!stream->is_open())
    {
        std::cout << "Не удалось открыть DAT файл" << std::endl;
        throw;
    }
    stream->seekg(offset, std::ios::beg);
    stream->readsome(data, size);
    stream->close();
    delete stream;
    return data;
}

}
