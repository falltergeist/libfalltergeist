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
}

File::File(std::string filename)
{
    setFilename(filename);
    _initialize();
}

File::~File()
{
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

    _stream = std::shared_ptr<std::ifstream>(new std::ifstream());
    _stream->open(filename(), std::ios_base::binary);
    if (!_stream->is_open())
    {
        throw Exception("File::_initialize() - can't open stream: " + filename());
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

std::vector<std::shared_ptr<Item>>* File::items()
{
    // if items are fetched already
    if (_items.size()) return &_items;

        unsigned int oldPos = position();

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
            auto entry = std::shared_ptr<Entry>(new Entry(this));

            *this >> *entry;

            std::string extension = entry->filename().substr(entry->filename().length() - 3, 3);

            std::shared_ptr<Item> item;
            if      (extension == "aaf") item = std::shared_ptr<Aaf::File>(new Aaf::File(entry));
            else if (extension == "acm") item = std::shared_ptr<Acm::File>(new Acm::File(entry));
            else if (extension == "bio") item = std::shared_ptr<Bio::File>(new Bio::File(entry));
            else if (extension == "fon") item = std::shared_ptr<Fon::File>(new Fon::File(entry));
            else if (extension == "frm") item = std::shared_ptr<Frm::File>(new Frm::File(entry));
            else if (extension == "gam") item = std::shared_ptr<Gam::File>(new Gam::File(entry));
            else if (extension == "gcd") item = std::shared_ptr<Gcd::File>(new Gcd::File(entry));
            else if (extension == "int") item = std::shared_ptr<Int::File>(new Int::File(entry));
            else if (extension == "lip") item = std::shared_ptr<Lip::File>(new Lip::File(entry));
            else if (extension == "lst") item = std::shared_ptr<Lst::File>(new Lst::File(entry));
            else if (extension == "map") item = std::shared_ptr<Map::File>(new Map::File(entry));
            else if (extension == "msg") item = std::shared_ptr<Msg::File>(new Msg::File(entry));
            else if (extension == "mve") item = std::shared_ptr<Mve::File>(new Mve::File(entry));
            else if (extension == "pal") item = std::shared_ptr<Pal::File>(new Pal::File(entry));
            else if (extension == "pro") item = std::shared_ptr<Pro::File>(new Pro::File(entry));
            else if (extension == "rix") item = std::shared_ptr<Rix::File>(new Rix::File(entry));
            else if (extension == "sve") item = std::shared_ptr<Sve::File>(new Sve::File(entry));
            else item = std::shared_ptr<Item>(new Item(entry));

            _items.push_back(item);
        }
        setPosition(oldPos);

    return &_items;
}

std::shared_ptr<Item> File::item(const std::string filename)
{
    std::string name(filename);
    // Replace slashes and transform to lower case
    std::replace(name.begin(),name.end(),'\\','/');
    std::transform(name.begin(),name.end(),name.begin(), ::tolower);


    for (auto item : *items())
    {
        if (name.compare(item->filename()) == 0)
        {
            return item;
        }
    }
    return 0;
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
