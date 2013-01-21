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
#include <iostream>

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
    _stream->open(pathToFile, std::ios::binary);
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
 * Returns curent position in file
 * @brief DatFile::getPosition
 * @return
 */
unsigned int DatFile::getPosition()
{
    return _stream->tellg();
}

/**
 * Returns file size in bytes
 * @brief DatFile::size
 * @return
 */
unsigned int DatFile::size(void)
{
    if (!_stream || !_stream->is_open()) return 0;
    unsigned int oldPosition = _stream->tellg();
    _stream->seekg(0,std::ios::end);
    unsigned int currentPosition = _stream->tellg();
    _stream->seekg(oldPosition, std::ios::beg);
    return currentPosition;
}

/**
 * Returns DatFile entries
 * @brief DatFile::getItems
 * @return
 */
std::vector<DatFileItem *> * DatFile::getItems()
{
    if (_items == 0)
    {
        std::cout << "Loading items..." << std::endl;
        setPosition(size() - 4);
        std::cout << "Total data size: " << readUint32() << std::endl;
        std::cout << "Position: " << getPosition() << std::endl;
    }
    return _items;
}

unsigned int DatFile::readUint32()
{
    unsigned int value;
    unsigned char * data = new unsigned char[4]();
    _stream->readsome((char *)data, 4);
    value = ( data[3] << 24) | (data[2] << 16) | ( data[1] << 8) | data[0];
    delete [] data;
    //setPosition(getPosition() + 4);
    return value;
}

int DatFile::readInt32()
{
    return (int) readUint32();
}

unsigned short DatFile::readUint16()
{
    unsigned short value;
    unsigned char * data = new unsigned char[2]();
    _stream->readsome((char *)data, 2);
    value = ( data[1] << 8) | data[0];
    delete [] data;
    //setPosition(getPosition() + 2);
    return value;
}

short DatFile::readInt16()
{
    return (short) readUint16();
}

unsigned char DatFile::readUint8()
{
    unsigned char value;
    _stream->readsome((char *)&value, 1);
    return value;
}

char DatFile::readInt8()
{
    return (char) readUint8();
}

}
