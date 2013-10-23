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
    std::vector<DatFileItem *> * _items;
    std::ifstream * _stream;
    std::string _pathToFile;
public:
    DatFile();
    DatFile(std::string pathToFile);
    virtual ~DatFile();

    std::string pathToFile();

    bool open(const std::string pathToFile);
    bool isOpened();
    void readBytes(char * destination, unsigned int numberOfBytes);
    void skipBytes(unsigned int numberOfBytes);

    void setPosition(unsigned int position);
    unsigned int position();

    unsigned int size();

    virtual std::vector<DatFileItem *> * items();

    DatFile& operator>>(int &value);
    DatFile& operator>>(unsigned int &value);
    DatFile& operator>>(short &value);
    DatFile& operator>>(unsigned short &value);
    DatFile& operator>>(char &value);
    DatFile& operator>>(unsigned char &value);
    DatFile& operator>>(DatFileEntry &entry);

    DatFileItem * item(std::string filename);

};

}

#endif // LIBFALLTERGEIST_DATFILE_H
