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
#include <string>
#include <iostream>

// libfalltergeist includes
#include "../src/DatFile.h"
#include "../src/DatFileItem.h"
#include "../src/Exception.h"

// Third party includes

namespace libfalltergeist
{

/**
 * Creates empty DAT file with no filename
 * @brief DatFile::DatFile
 */
DatFile::DatFile()
{
    _items = 0;
    _stream = 0;
}

/**
 * Opens selected DAT file
 * @brief DatFile::DatFile
 */
DatFile::DatFile(std::string pathToFile)
{
    _items = 0;
    _stream = 0;
    open(pathToFile);
}

/**
 * Destroys DAT file object
 * @brief DatFile::~DatFile
 */
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

/**
 * Check if file is opened
 * @brief DatFile::isOpened
 * @return
 */
bool DatFile::isOpened()
{
    if (_stream && _stream->is_open())
    {
        return true;
    }
    return false;
}

/**
 * Closes file stream
 * @brief DatFile::close
 * @return
 */
bool DatFile::close()
{
    if (_stream && _stream->is_open())
    {
        _stream->close();
        if (_stream->is_open())
        {
            return false;
        }
        else
        {
            return true;
        }
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
        _items = new std::vector<DatFileItem *>;

        unsigned int datFileSize;
        unsigned int filesTreeSize;
        unsigned int filesTotalNumber;

        // reading data size from dat file
        setPosition(size() - 4);        
        *this >> datFileSize;
        std::cout << datFileSize << "|" << size() << std::endl;
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
            DatFileItem * item = new DatFileItem(this);

            *this >> *item;

            _items->push_back(item);
        }
    }
    return _items;
}

/**
 * Returns item by filename
 * @brief DatFile::getItem
 * @param filename
 * @return
 */
DatFileItem * DatFile::item(const std::string filename)
{
    std::string name(filename);
    // Replace slashes and transform to lower case
    std::replace(name.begin(),name.end(),'\\','/');
    std::transform(name.begin(),name.end(),name.begin(), ::tolower);
    std::vector<DatFileItem *>::iterator it;
    for (it = this->items()->begin(); it != this->items()->end(); ++it)
    {
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

DatFile& DatFile::operator>>(DatFileItem& item)
{
    unsigned int filenameSize;
    unsigned char compressed;
    unsigned int unpackedSize;
    unsigned int packedSize;
    unsigned int dataOffset;

    *this >> filenameSize;

    char * filename = new char[filenameSize + 1]();
    readBytes(filename, filenameSize);
    item.setFilename(filename);
    delete [] filename;

    *this >> compressed >> unpackedSize >> packedSize >> dataOffset;

    item.setCompressed((bool) compressed);
    item.setUnpackedSize(unpackedSize);
    item.setPackedSize(packedSize);
    item.setDataOffset(dataOffset);

    return *this;
}

}
