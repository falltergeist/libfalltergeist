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
#include <fstream>
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
}

/**
 * Opens existing file if exist or creates new
 * @brief DatFile::DatFile
 * @param pathToFile
 */
DatFile::DatFile(char * pathToFile)
{
    _items = 0;
    // trying to open file
    std::ifstream stream(pathToFile, std::ios::binary);
    if (stream.is_open())
    {
        std::cout << "DAT file opened" << std::endl;
    }
    else
    {
        std::cout << "Can't open DAT file" << std::endl;
    }

}

/**
 * Destroys DAT file object
 * @brief DatFile::~DatFile
 */
DatFile::~DatFile()
{
    delete _items;
}

/**
 * Opens existing DAT file
 * @brief DatFile::open
 * @param pathToFile
 * @return
 */
bool DatFile::open(char * pathToFile)
{
}

/**
 * Saves object to file
 * @brief DatFile::save
 * @param pathToFile
 * @return
 */
bool DatFile::save(char * pathToFile)
{
}

/**
 * Closes file
 * @brief DatFile::close
 * @return
 */
bool DatFile::close()
{
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
