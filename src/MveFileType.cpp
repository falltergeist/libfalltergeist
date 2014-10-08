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
#include <cstring>

// libfalltergeist includes
#include "../src/MveFileType.h"
#include "../src/Exception.h"

// Third party includes

namespace libfalltergeist
{

MveFileType::MveFileType(std::shared_ptr<DatFileEntry> datFileEntry) : DatFileItem(datFileEntry)
{
}

MveFileType::MveFileType(std::ifstream* stream) : DatFileItem(stream)
{
}

MveFileType::~MveFileType()
{
}

void MveFileType::_initialize()
{
    if (_initialized) return;
    DatFileItem::_initialize();
    DatFileItem::setPosition(0);
    setEndianness(ENDIANNESS_LITTLE);
    // header
    const char  MVE_HEADER[]  = "Interplay MVE File\x1A";
    const int16_t MVE_HDRCONST1 = 0x001A;
    const int16_t MVE_HDRCONST2 = 0x0100;
    const int16_t MVE_HDRCONST3 = 0x1133;
    int16_t check1, check2, check3;
 
    char head[20];
    readBytes((char*)head,20);

    if (strncmp(head,MVE_HEADER,20)!=0)
    {
        throw Exception("Invalid MVE file.!");
    }
    *this >> check1 >> check2 >> check3;
    if  (!(check1 == MVE_HDRCONST1 && check2 == MVE_HDRCONST2 && check3 == MVE_HDRCONST3))
    {
        throw Exception("Invalid MVE file.");
    }
}

std::shared_ptr<MveChunk> MveFileType::getNextChunk()
{
    _initialize();
    if (this->position() < this->size())
    {
        auto chunk = std::shared_ptr<MveChunk>(new MveChunk());
        *this >> chunk->length >> chunk->type;
        for (unsigned int i = 0; i < chunk->length;)
        {
            auto opcode = std::shared_ptr<MveOpcode>(new MveOpcode());
            *this >> opcode->length >> opcode->type >> opcode->version;
            opcode->data = new uint8_t [opcode->length];
            this->readBytes((char*)opcode->data, opcode->length);
            chunk->opcodes.push_back(opcode);
            i+=opcode->length+4;
        }
        return chunk;
    }
    return nullptr;
}

}
