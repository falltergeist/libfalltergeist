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
#include "../src/AcmFileType.h"

// Third party includes

#include "general.h"
#include "Exception.h"

namespace libfalltergeist
{

AcmFileType::AcmFileType(std::shared_ptr<DatFileEntry> datFileEntry)
        : DatFileItem(datFileEntry), block(nullptr)
{
}

AcmFileType::AcmFileType(std::ifstream* stream)
        : DatFileItem(stream), block(nullptr)
{
}

AcmFileType::~AcmFileType()
{
    if (block != nullptr)
    {
        free(block);
        block = nullptr;
    }
}

void AcmFileType::_initialize()
{
    if (_initialized) return;
    this->setEndianness(ENDIANNESS_LITTLE);


    DatFileItem::_initialize();
    DatFileItem::setPosition(0);

    ACM_Header hdr;
    *this >> hdr.signature;
    *this >> hdr.samples;
    *this >> hdr.channels;
    *this >> hdr.rate;

    int16_t tmpword;
    readBytes((char *) &tmpword, 2);
    subblocks = (int) (tmpword>>4);
    levels = (int) (tmpword&15);

    if (hdr.signature != IP_ACM_SIG)
    {
        throw Exception("Not an ACM file - invalid signature");
    }

    samples_left = ( _samples = hdr.samples );
    _channels = hdr.channels;
    _bitrate = hdr.rate;
    block_size = ( 1 << levels ) * subblocks;

    block = (int *) malloc(sizeof(int)*block_size);

    unpacker = std::shared_ptr<CValueUnpacker>(new CValueUnpacker(levels, subblocks, this));
    if (!unpacker || !unpacker->init_unpacker())
    {
        throw Exception("Cannot create or init unpacker");
    }
    decoder = std::shared_ptr<CSubbandDecoder>(new CSubbandDecoder(levels));
    if (!decoder || !decoder->init_decoder())
    {
        throw Exception("Cannot create or init decoder");
    }
}

void AcmFileType::init()
{
    _initialize();
}


int AcmFileType::make_new_samples()
{
    if (!unpacker->get_one_block( block ))
    {
        // FIXME: is it an error or the end of the stream?
        return 0;
    }
    decoder->decode_data( block, subblocks );
    values = block;
    samples_ready = ( block_size > samples_left ) ? samples_left : block_size;
    samples_left -= samples_ready;
    return 1;
}

int AcmFileType::read_samples(short* buffer, int count)
{
    int res = 0;
    while (res < count) {
        if (samples_ready == 0) {
            if (samples_left == 0)
                break;
            if (!make_new_samples())
                break;
        }
        *buffer = ( short ) ( ( *values ) >> levels );
        values++;
        buffer++;
        res += 1;
        samples_ready--;
    }
    return res;
}

int AcmFileType::samples() const
{
    return _samples;
}

int AcmFileType::channels() const
{
    return _channels;
}

int AcmFileType::bitrate() const
{
    return _bitrate;
}

}
