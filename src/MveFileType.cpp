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

// libfalltergeist includes
#include "../src/MveFileType.h"

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
}

void MveFileType::test()
{
    _initialize();

    setEndianness(ENDIANNESS_LITTLE);

    // header
    this->skipBytes(26);

    while (this->position() < this->size())
    {
        // chunk header
        unsigned short chunkSize;
        unsigned short chunkType;
        *this >> chunkSize >> chunkType;
        //std::cout << "chunk - type: " << chunkType << " size: " << chunkSize << std::endl;

        // chunk data
        for (unsigned int i = 0; i < chunkSize;)
        {
            // opcode header
            unsigned short opcodeSize;
            unsigned char opcodeType;
            unsigned char opcodeVersion;
            *this >> opcodeSize >> opcodeType >> opcodeVersion;
            //std::cout << " opcode - type: " << (int) opcodeType << " size: " << opcodeSize << " version: " << (int) opcodeVersion << std::endl;

            // opcode data
            switch(opcodeType)
            {
                case 0x05: // Initialize Video Buffer
                {
                    unsigned short width;
                    unsigned short height;
                    *this >> width >> height;

                    if (opcodeVersion == 1) this->skipBytes(2);
                    if (opcodeVersion == 2) this->skipBytes(4);

                    //std::cout << "  Init Video Buffer: " << width << "x" << height << std::endl;

                    break;
                }
                case 0x0A: // Initialize Video Mode
                {
                    unsigned short width;
                    unsigned short height;
                    unsigned short flags;
                    *this >> width >> height >> flags;
                    //std::cout << "  Init Video Mode: " << width << "x" << height << " - " << flags << std::endl;
                    break;
                }
                case 0x0C: // Set palette
                {
                    unsigned short start;
                    unsigned short count;
                    *this >> start >> count;

                    //std::cout << "  Set Palette: " << start << " - " << count << std::endl;

                    // data
                    this->skipBytes(count * 3);
                    break;
                }
                default:
                {
                    this->skipBytes(opcodeSize);
                }
            }







            i += opcodeSize + 4;
        }


    }
}

}
