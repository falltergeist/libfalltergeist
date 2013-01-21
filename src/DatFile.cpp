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
 * Opens existing DAT file
 * @brief DatFile::open
 * @param pathToFile
 * @return
 */
bool DatFile::open(char * pathToFile)
{
    std::cout << "opening DAT file..." << std::endl;
    _stream = new std::ifstream();
    _stream->open(pathToFile, std::ios::binary);
    if (_stream->is_open())
    {
        std::cout << "DAT file opened" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Can't open DAT file" << std::endl;
        return false;
    }
}

/**
 * Closes file
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

unsigned int DatFile::size(void)
{
    if (!_stream || !_stream->is_open()) return 0;
    _stream->seekg(0,std::ios::end);
    return _stream->tellg();
}

std::vector<DatFileItem *> * DatFile::getItems()
{
    if (_items == 0)
    {
        //load items;
        std::cout << "Loading items..." << std::endl;
    }
    return _items;
}

}
