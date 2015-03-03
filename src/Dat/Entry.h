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

#ifndef LIBFALLTERGEIST_DAT_ENTRY_H
#define LIBFALLTERGEIST_DAT_ENTRY_H

// C++ standard includes
#include <cstdint>
#include <memory>
#include <string>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
namespace Dat
{
class File;

class Entry
{

public:
    Entry(File* datFile);
    ~Entry();

    std::string filename();
    void setFilename(std::string value);

    uint32_t packedSize();
    void setPackedSize(uint32_t value);

    uint32_t unpackedSize();
    void setUnpackedSize(uint32_t value);

    uint32_t dataOffset();
    void setDataOffset(uint32_t value);

    bool compressed();
    void setCompressed(bool value);

    File* datFile();

protected:
    File* _datFile;
    std::string _filename;
    uint32_t _packedSize;
    uint32_t _unpackedSize;
    uint32_t _dataOffset;
    bool _compressed;


};

}
}
#endif // LIBFALLTERGEIST_DAT_ENTRY_H
