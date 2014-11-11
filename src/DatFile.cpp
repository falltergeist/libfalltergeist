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

// C++ standard includes
#include <algorithm>

// libfalltergeist includes
#include "../src/DatFile.h"
#include "../src/DatFileItem.h"
#include "../src/DatFileEntry.h"
#include "../src/Exception.h"
#include "../src/AafFileType.h"
#include "../src/AcmFileType.h"
#include "../src/BioFileType.h"
#include "../src/FonFileType.h"
#include "../src/FrmFileType.h"
#include "../src/GamFileType.h"
#include "../src/GcdFileType.h"
#include "../src/IntFileType.h"
#include "../src/MapFileType.h"
#include "../src/MsgFileType.h"
#include "../src/MveFileType.h"
#include "../src/LipFileType.h"
#include "../src/LstFileType.h"
#include "../src/PalFileType.h"
#include "../src/ProFileType.h"
#include "../src/RixFileType.h"
#include "../src/SveFileType.h"

// Third party includes

namespace libfalltergeist
{

DatFile::DatFile()
{
}

DatFile::DatFile(std::string filename)
{
    setFilename(filename);
    _initialize();
}

DatFile::~DatFile()
{
}

std::string DatFile::filename()
{
    return _filename;
}

DatFile* DatFile::setFilename(std::string filename)
{
    _filename = filename;
    return this;
}

void DatFile::_initialize()
{
    if (_initialized) return;
    _initialized = true;

    _stream = std::shared_ptr<std::ifstream>(new std::ifstream());
    _stream->open(filename(), std::ios_base::binary);
    if (!_stream->is_open())
    {
        throw Exception("DatFile::_initialize() - can't open stream: " + filename());
    }
}

DatFile* DatFile::setPosition(unsigned int position)
{
    _stream->seekg(position, std::ios::beg);
    return this;
}

unsigned int DatFile::position()
{
    return _stream->tellg();
}

unsigned int DatFile::size(void)
{
    auto oldPosition = _stream->tellg();
    _stream->seekg(0,std::ios::end);
    auto currentPosition = _stream->tellg();
    _stream->seekg(oldPosition, std::ios::beg);
    return currentPosition;
}

DatFile* DatFile::skipBytes(unsigned int numberOfBytes)
{
    setPosition(position() + numberOfBytes);
    return this;
}

DatFile* DatFile::readBytes(char * destination, unsigned int numberOfBytes)
{
    unsigned int position = this->position();
    _stream->read(destination, numberOfBytes);
    setPosition(position + numberOfBytes);
    return this;
}

std::vector<std::shared_ptr<DatFileItem>>* DatFile::items()
{
    // if items are fetched already
    if (_items.size()) return &_items;

        unsigned int oldPos = position();

        unsigned int datFileSize;
        unsigned int filesTreeSize;
        unsigned int filesTotalNumber;

        // reading data size from dat file
        setPosition(size() - 4);
        *this >> datFileSize;
        if (datFileSize != size())
        {
            throw Exception("DatFile::items() - wrong file size");
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
            auto entry = std::shared_ptr<DatFileEntry>(new DatFileEntry(this));

            *this >> *entry;

            std::string extension = entry->filename().substr(entry->filename().length() - 3, 3);

            std::shared_ptr<DatFileItem> item;
            if      (extension == "aaf") item = std::shared_ptr<AafFileType>(new AafFileType(entry));
            else if (extension == "acm") item = std::shared_ptr<AcmFileType>(new AcmFileType(entry));
            else if (extension == "bio") item = std::shared_ptr<BioFileType>(new BioFileType(entry));
            else if (extension == "fon") item = std::shared_ptr<FonFileType>(new FonFileType(entry));
            else if (extension == "frm") item = std::shared_ptr<FrmFileType>(new FrmFileType(entry));
            else if (extension == "gam") item = std::shared_ptr<GamFileType>(new GamFileType(entry));
            else if (extension == "gcd") item = std::shared_ptr<GcdFileType>(new GcdFileType(entry));
            else if (extension == "int") item = std::shared_ptr<IntFileType>(new IntFileType(entry));
            else if (extension == "lip") item = std::shared_ptr<LipFileType>(new LipFileType(entry));
            else if (extension == "lst") item = std::shared_ptr<LstFileType>(new LstFileType(entry));
            else if (extension == "map") item = std::shared_ptr<MapFileType>(new MapFileType(entry));
            else if (extension == "msg") item = std::shared_ptr<MsgFileType>(new MsgFileType(entry));
            else if (extension == "mve") item = std::shared_ptr<MveFileType>(new MveFileType(entry));
            else if (extension == "pal") item = std::shared_ptr<PalFileType>(new PalFileType(entry));
            else if (extension == "pro") item = std::shared_ptr<ProFileType>(new ProFileType(entry));
            else if (extension == "rix") item = std::shared_ptr<RixFileType>(new RixFileType(entry));
            else if (extension == "sve") item = std::shared_ptr<SveFileType>(new SveFileType(entry));
            else item = std::shared_ptr<DatFileItem>(new DatFileItem(entry));

            _items.push_back(item);
        }
        setPosition(oldPos);

    return &_items;
}

std::shared_ptr<DatFileItem> DatFile::item(const std::string filename)
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

DatFile& DatFile::operator>>(int &value)
{
    readBytes(reinterpret_cast<char *>(&value), sizeof(value));
    return *this;
}

DatFile& DatFile::operator>>(unsigned int &value)
{
    return *this >> (int&) value;
}

DatFile& DatFile::operator>>(short &value)
{
    readBytes(reinterpret_cast<char *>(&value), sizeof(value));
    return *this;
}

DatFile& DatFile::operator>>(unsigned short &value)
{
    return *this >> (short&) value;
}

DatFile& DatFile::operator>>(char &value)
{
    readBytes(reinterpret_cast<char *>(&value), sizeof(value));
    return *this;
}

DatFile& DatFile::operator>>(unsigned char &value)
{
    return *this >> (char&) value;
}

DatFile& DatFile::operator>>(DatFileEntry& entry)
{
    unsigned int filenameSize;
    unsigned char compressed;
    unsigned int unpackedSize;
    unsigned int packedSize;
    unsigned int dataOffset;

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
