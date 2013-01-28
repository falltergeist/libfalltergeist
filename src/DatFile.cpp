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
    _items = 0;
    _stream = 0;
}

/**
 * Opens selected DAT file
 * @brief DatFile::DatFile
 */
DatFile::DatFile(char * pathToFile)
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

/**
 * Opens file stream
 * @brief DatFile::open
 * @param pathToFile
 * @return
 */
bool DatFile::open(char * pathToFile)
{
    std::cout << "Opening DAT file: " << pathToFile << " ... ";
    _stream = new std::ifstream();
    _stream->open(pathToFile, std::ios_base::binary);
    if (_stream->is_open())
    {
        std::cout << "[OK]" << std::endl;
        return true;
    }
    else
    {
        std::cout << "[FAIL]" << std::endl;
        return false;
    }
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

/**
 * Sets current position in file
 * @brief DatFile::setPosition
 * @param position
 */
void DatFile::setPosition(unsigned int position)
{
    _stream->seekg(position, std::ios::beg);
}

/**
 * Alias to getPosition
 * @brief DatFile::position
 * @return
 */
unsigned int DatFile::position()
{
    return getPosition();
}

/**
 * Returns curent position in file
 * @brief DatFile::getPosition
 * @return
 */
unsigned int DatFile::getPosition()
{
    return _stream->tellg();
}

/**
 * Alias to DatFile::getSize
 * @brief DatFile::size
 * @return
 */
unsigned int DatFile::size(void)
{
    return getSize();
}

/**
 * Returns file size in bytes
 * @brief DatFile::size
 * @return
 */
unsigned int DatFile::getSize(void)
{
    if (!_stream || !_stream->is_open()) return 0;
    unsigned int oldPosition = _stream->tellg();
    _stream->seekg(0,std::ios::end);
    unsigned int currentPosition = _stream->tellg();
    _stream->seekg(oldPosition, std::ios::beg);
    return currentPosition;
}

/**
 * Skips some bytes
 * @brief DatFile::skipBytes
 * @param numberOfBytes
 */
void DatFile::skipBytes(unsigned int numberOfBytes)
{
    setPosition(getPosition() + numberOfBytes);
}

/**
 * Reads some bytes to the selected destination
 * @brief DatFile::readBytes
 * @param destination
 * @param numberOfBytes
 */
void DatFile::readBytes(char * destination, unsigned int numberOfBytes)
{
    unsigned int position = getPosition();
    unsigned int readed = _stream->readsome(destination, numberOfBytes);
    setPosition(position + numberOfBytes);
}

/**
 * Alias to DatFile::getItems
 * @brief DatFile::items
 * @return
 */
std::vector<DatFileItem *> * DatFile::items()
{
    return getItems();
}

/**
 * Returns DatFile entries
 * @brief DatFile::getItems
 * @return
 */
std::vector<DatFileItem *> * DatFile::getItems()
{
    if (!isOpened()) return 0;

    if (_items == 0)
    {
        std::cout << "Loading DAT file items ... ";

        _items = new std::vector<DatFileItem *>;

        // reading data size from dat file
        setPosition(size() - 4);
        unsigned int datFileSize = readUint32();
        if (datFileSize != size())
        {
            std::cout << "[FAIL]" << std::endl;
            std::cout << "[ERROR] Wrong or corrupted DAT file";
            return 0;
        }

        // reading size of files tree
        setPosition(size() - 8);
        unsigned int filesTreeSize = readUint32();

        // reading total number of items in dat file
        setPosition(size() - filesTreeSize - 8);
        unsigned int filesTotalNumber = readUint32();

        //reading files data one by one
        for (unsigned int i = 0; i != filesTotalNumber; ++i)
        {
            DatFileItem * item = new DatFileItem(this);

            //reading fileName
            unsigned int filenameSize = readUint32();
            char * filename = new char[filenameSize + 1]();
            readBytes(filename, filenameSize);
            item->setFilename(filename);
            delete [] filename;

            //reading compression flag
            item->setCompressed(readUint8() == 1 ? true : false);

            //reading unpacked size
            item->setUnpackedSize(readUint32());

            //reading packed size
            item->setPackedSize(readUint32());

            //reading data offset from dat file begining
            item->setDataOffset(readUint32());

            _items->push_back(item);
        }
        std::cout << "[OK]" << std::endl;
        std::cout << "Items loaded: " << filesTotalNumber << std::endl;
    }
    return _items;
}

unsigned int DatFile::readUint32()
{
    unsigned int position = getPosition();
    unsigned int value;
    unsigned char * data = new unsigned char[4]();
    _stream->readsome((char *)data, 4);
    // Little endian
    value = ( data[3] << 24) | (data[2] << 16) | ( data[1] << 8) | data[0];
    delete [] data;
    setPosition(position + 4);
    return value;
}

int DatFile::readInt32()
{
    return (int) readUint32();
}

unsigned short DatFile::readUint16()
{
    unsigned int position = getPosition();
    unsigned short value;
    unsigned char * data = new unsigned char[2]();
    _stream->readsome((char *)data, 2);
    // Little endian
    value = ( data[1] << 8) | data[0];
    delete [] data;
    setPosition(position + 2);
    return value;
}

short DatFile::readInt16()
{
    return (short) readUint16();
}

unsigned char DatFile::readUint8()
{
    unsigned int position = getPosition();
    unsigned char value;
    _stream->readsome((char *)&value, 1);
    setPosition(position + +1);
    return value;
}

char DatFile::readInt8()
{
    return (char) readUint8();
}

/**
 * Alias to DatFile::getItem
 * @brief DatFile::item
 * @param filename
 * @return
 */
DatFileItem * DatFile::item(char * filename)
{
    return getItem(filename);
}

/**
 * Returns item by filename
 * @brief DatFile::getItem
 * @param filename
 * @return
 */
DatFileItem * DatFile::getItem(char * filename)
{
    std::string name(filename);
    // Replace slashes and transform to lower case
    std::replace(name.begin(),name.end(),'\\','/');
    std::transform(name.begin(),name.end(),name.begin(), ::tolower);
    std::vector<DatFileItem *>::iterator it;
    for (it = getItems()->begin(); it != getItems()->end(); ++it)
    {
        if ((*it)->getFilename() == name)
        {
            return *it;
        }
    }
    return 0;
}

}
