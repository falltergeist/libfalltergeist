/*
 * Copyright 2012-2014 Falltergeist Developers.
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

#ifndef LIBFALLTERGEIST_DATFILE_H
#define LIBFALLTERGEIST_DATFILE_H

// C++ standard includes
#include <vector>
#include <fstream>
#include <string>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
class DatFileItem;
class DatFileEntry;

class DatFile
{
protected:
    std::vector<DatFileItem *> * _items = 0;
    std::ifstream * _stream = 0;
    std::string _filename;
    bool _initialized = false;
    void _initialize();
public:
    DatFile();
    DatFile(std::string pathToFile);
    virtual ~DatFile();

    std::string filename();
    DatFile* setFilename(std::string filename);

    std::vector<DatFileItem*>* items();
    DatFileItem* item(std::string filename);

    DatFile* readBytes(char* destination, unsigned int numberOfBytes);
    DatFile* skipBytes(unsigned int numberOfBytes);
    DatFile* setPosition(unsigned int position);
    unsigned int position();
    unsigned int size();

    DatFile& operator>>(int &value);
    DatFile& operator>>(unsigned int &value);
    DatFile& operator>>(short &value);
    DatFile& operator>>(unsigned short &value);
    DatFile& operator>>(char &value);
    DatFile& operator>>(unsigned char &value);
    DatFile& operator>>(DatFileEntry &entry);
};

}

#endif // LIBFALLTERGEIST_DATFILE_H
