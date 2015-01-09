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

#ifndef LIBFALLTERGEIST_DATFILEENTRY_H
#define LIBFALLTERGEIST_DATFILEENTRY_H

// C++ standard includes
#include <string>
#include <memory>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
class DatFile;

class DatFileEntry
{
protected:
    DatFile* _datFile;
    std::string _filename;
    unsigned int _packedSize;
    unsigned int _unpackedSize;
    unsigned int _dataOffset;
    bool _compressed;
public:
    DatFileEntry(DatFile* datFile);
    ~DatFileEntry();

    std::string filename() const;
    void setFilename(std::string value);

    unsigned int packedSize() const;
    void setPackedSize(unsigned int value);

    unsigned int unpackedSize() const;
    void setUnpackedSize(unsigned int value);

    unsigned int dataOffset() const;
    void setDataOffset(unsigned int value);

    bool compressed() const;
    void setCompressed(bool value);

    DatFile* datFile() const;

};

}
#endif // LIBFALLTERGEIST_DATFILEENTRY_H
