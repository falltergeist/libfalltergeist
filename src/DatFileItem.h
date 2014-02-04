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

#ifndef LIBFALLTERGEIST_DATFILEITEM_H
#define LIBFALLTERGEIST_DATFILEITEM_H

// C++ standard includes
#include <string>
#include <fstream>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
class DatFileEntry;

class DatFileItem: public std::streambuf
{
protected:    
    std::string _filename;
    DatFileEntry* _datFileEntry = 0;
    std::ifstream* _stream = 0;


    char* _buffer = 0;
    int _size;
    int _endianness = ENDIANNESS_BIG;

    bool _initialized = false;
    virtual void _initialize();

public:
    enum Endianness {ENDIANNESS_BIG = 0, ENDIANNESS_LITTLE};

    DatFileItem(std::ifstream* stream);
    DatFileItem(DatFileEntry* datFileEntry);
    ~DatFileItem();

    virtual std::streambuf::int_type underflow();

    DatFileItem* setFilename(const std::string filename);
    std::string filename();

    DatFileItem* readBytes(char* destination, unsigned int size);
    DatFileItem* skipBytes(unsigned int numberOfBytes);
    DatFileItem* setPosition(unsigned int position);
    unsigned int position();
    unsigned int size();

    int endianness();
    void setEndianness(int value);

    DatFileItem& operator>>(unsigned int &value);
    DatFileItem& operator>>(int &value);
    DatFileItem& operator>>(unsigned short &value);
    DatFileItem& operator>>(short &value);
    DatFileItem& operator>>(unsigned char &value);
    DatFileItem& operator>>(char &value);


};

}
#endif //LIBFALLTERGEIST_DATFILEITEM_H
