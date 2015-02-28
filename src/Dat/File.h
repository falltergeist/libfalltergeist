/*
 * Copyright 2012-2015 Falltergeist Developers.
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

#ifndef LIBFALLTERGEIST_DAT_FILE_H
#define LIBFALLTERGEIST_DAT_FILE_H

// C++ standard includes
#include <cstdint>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
namespace Dat
{

class Item;
class Entry;

class File
{
protected:
    std::vector<std::shared_ptr<Item>> _items;
    std::shared_ptr<std::ifstream> _stream;
    std::string _filename;
    bool _initialized = false;
    void _initialize();
public:
    File();
    File(std::string pathToFile);
    virtual ~File();

    std::string filename();
    File* setFilename(std::string filename);

    std::vector<std::shared_ptr<Item>>* items();
    std::shared_ptr<Item> item(std::string filename);

    File* readBytes(char* destination, unsigned int numberOfBytes);
    File* skipBytes(unsigned int numberOfBytes);
    File* setPosition(unsigned int position);
    unsigned int position();
    unsigned int size();

    File& operator>>(int32_t &value);
    File& operator>>(uint32_t &value);
    File& operator>>(int16_t &value);
    File& operator>>(uint16_t &value);
    File& operator>>(int8_t &value);
    File& operator>>(uint8_t &value);
    File& operator>>(Entry &entry);
};

}
}
#endif // LIBFALLTERGEIST_DAT_FILE_H
