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

// C++ standard includes
#include <algorithm>

// libfalltergeist includes
#include "../Aaf/File.h"
#include "../Acm/File.h"
#include "../Bio/File.h"
#include "../Dat/Entry.h"
#include "../Dat/File.h"
#include "../Dat/Item.h"
#include "../Exception.h"
#include "../Fon/File.h"
#include "../Frm/File.h"
#include "../Gam/File.h"
#include "../Gcd/File.h"
#include "../Int/File.h"
#include "../Map/File.h"
#include "../Msg/File.h"
#include "../Mve/File.h"
#include "../Lip/File.h"
#include "../Lst/File.h"
#include "../Pal/File.h"
#include "../Pro/File.h"
#include "../Rix/File.h"
#include "../Sve/File.h"

// Third party includes

namespace libfalltergeist
{
namespace Dat
{

File::File()
{
    _initialize();
}

File::File(std::string filename)
{
    setFilename(filename);
    _initialize();
}

File::~File()
{
    for (auto item : _items)
    {
        delete item.second;
    }

    for (auto entry : _entries)
    {
        delete entry;
    }
    delete _stream;
}

std::string File::filename()
{
    return _filename;
}

File* File::setFilename(std::string filename)
{
    _filename = filename;
    return this;
}

void File::_initialize()
{
    if (_initialized) return;
    _initialized = true;

    _stream = new std::ifstream();
    _stream->open(filename(), std::ios_base::binary);
    if (!_stream->is_open())
    {
        throw Exception("File::_initialize() - can't open stream: " + filename());
    }

    unsigned int FileSize;
    unsigned int filesTreeSize;
    unsigned int filesTotalNumber;

    // reading data size from dat file
    setPosition(size() - 4);
    *this >> FileSize;
    if (FileSize != size())
    {
        throw Exception("File::items() - wrong file size");
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
        auto entry = new Entry(this);

        *this >> *entry;

        _entries.push_back(entry);
    }
}

File* File::setPosition(unsigned int position)
{
    _stream->seekg(position, std::ios::beg);
    return this;
}

unsigned int File::position()
{
    return _stream->tellg();
}

unsigned int File::size(void)
{
    auto oldPosition = _stream->tellg();
    _stream->seekg(0,std::ios::end);
    auto currentPosition = _stream->tellg();
    _stream->seekg(oldPosition, std::ios::beg);
    return currentPosition;
}

File* File::skipBytes(unsigned int numberOfBytes)
{
    setPosition(position() + numberOfBytes);
    return this;
}

File* File::readBytes(char * destination, unsigned int numberOfBytes)
{
    unsigned int position = this->position();
    _stream->read(destination, numberOfBytes);
    setPosition(position + numberOfBytes);
    return this;
}

Item* File::item(const std::string filename)
{
    if (_items.find(filename) != _items.end())
    {
        return _items.at(filename);
    }

    for (auto entry : _entries)
    {
        if (entry->filename() != filename) continue;

        std::string extension = filename.substr(filename.length() - 3, 3);

        Item* item = nullptr;
        if      (extension == "aaf") item = new Aaf::File(entry);
        else if (extension == "acm") item = new Acm::File(entry);
        else if (extension == "bio") item = new Bio::File(entry);
        else if (extension == "fon") item = new Fon::File(entry);
        else if (extension == "frm") item = new Frm::File(entry);
        else if (extension == "gam") item = new Gam::File(entry);
        else if (extension == "gcd") item = new Gcd::File(entry);
        else if (extension == "int") item = new Int::File(entry);
        else if (extension == "lip") item = new Lip::File(entry);
        else if (extension == "lst") item = new Lst::File(entry);
        else if (extension == "map") item = new Map::File(entry);
        else if (extension == "msg") item = new Msg::File(entry);
        else if (extension == "mve") item = new Mve::File(entry);
        else if (extension == "pal") item = new Pal::File(entry);
        else if (extension == "pro") item = new Pro::File(entry);
        else if (extension == "rix") item = new Rix::File(entry);
        else if (extension == "sve") item = new Sve::File(entry);
        else item = new Item(entry);

        _items.insert(std::make_pair(filename, item));
        return item;
    }

    return nullptr;
}

File& File::operator>>(int32_t &value)
{
    readBytes(reinterpret_cast<char *>(&value), sizeof(value));
    return *this;
}

File& File::operator>>(uint32_t &value)
{
    return *this >> (int32_t&) value;
}

File& File::operator>>(int16_t &value)
{
    readBytes(reinterpret_cast<char *>(&value), sizeof(value));
    return *this;
}

File& File::operator>>(uint16_t &value)
{
    return *this >> (int16_t&) value;
}

File& File::operator>>(int8_t &value)
{
    readBytes(reinterpret_cast<char *>(&value), sizeof(value));
    return *this;
}

File& File::operator>>(uint8_t &value)
{
    return *this >> (int8_t&) value;
}

File& File::operator>>(Entry& entry)
{
    uint32_t filenameSize;
    uint8_t compressed;
    uint32_t unpackedSize;
    uint32_t packedSize;
    uint32_t dataOffset;

    *this >> filenameSize;

    std::string filename;
    filename.resize(filenameSize);
    readBytes(&filename[0], filenameSize);
    entry.setFilename(filename);

    *this >> compressed >> unpackedSize >> packedSize >> dataOffset;

    entry.setCompressed((bool) compressed);
    entry.setUnpackedSize(unpackedSize);
    entry.setPackedSize(packedSize);
    entry.setDataOffset(dataOffset);

    return *this;
}

}
}
