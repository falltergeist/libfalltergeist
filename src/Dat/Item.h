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

#ifndef LIBFALLTERGEIST_DAT_ITEM_H
#define LIBFALLTERGEIST_DAT_ITEM_H

// C++ standard includes
#include <fstream>
#include <string>
#include <memory>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
namespace Dat
{

class Entry;

enum Endianness {ENDIANNESS_BIG = 0, ENDIANNESS_LITTLE};

class Item: public std::streambuf
{

public:

    Item(std::ifstream* stream);
    Item(Dat::Entry* datFileEntry);
    ~Item();

    virtual std::streambuf::int_type underflow();

    Item* setFilename(const std::string filename);
    std::string filename();

    Item* readBytes(char* destination, unsigned int size);
    Item* skipBytes(unsigned int numberOfBytes);
    Item* setPosition(unsigned int position);
    unsigned int position();
    unsigned int size();

    unsigned int bytesRemains();

    Endianness endianness();
    void setEndianness(Endianness value);

    uint32_t uint32();
    int32_t int32();
    uint16_t uint16();
    int16_t int16();
    uint8_t uint8();
    int8_t int8();

    Item& operator>>(uint32_t &value);
    Item& operator>>(int32_t &value);
    Item& operator>>(uint16_t &value);
    Item& operator>>(int16_t &value);
    Item& operator>>(uint8_t &value);
    Item& operator>>(int8_t &value);

protected:
    std::string _filename;
    Entry* _datFileEntry = nullptr;
    std::ifstream* _stream = nullptr;

    uint8_t* _buffer = nullptr;
    int32_t _size;
    Endianness _endianness = ENDIANNESS_BIG;

    bool _initialized = false;
    virtual void _initialize();

};

}
}
#endif //LIBFALLTERGEIST_DAT_ITEM_H
