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

// DISCLAIMER.
// This code was taken from the ACMReader plugin of the GemRB project (http://gemrb.org)
// and then adapted for libfalltergeist. All credit goes to the original authors.
// Link to the plugin: https://github.com/gemrb/gemrb/tree/8e759bc6874a80d4a8d73bf79603624465b3aeb0/gemrb/plugins/ACMReader

// C++ standard includes

// libfalltergeist includes
#include "../Acm/File.h"
#include "../Acm/Decoder.h"
#include "../Acm/General.h"
#include "../Acm/Unpacker.h"
#include "../Exception.h"

// Third party includes

namespace libfalltergeist
{
namespace Acm
{

File::File(Dat::Entry* datFileEntry) : Dat::Item(datFileEntry)
{
    _initialize();
}

File::File(std::ifstream* stream) : Dat::Item(stream)
{
    _initialize();
}

File::~File()
{
    if (_block != nullptr)
    {
        free(_block);
        _block = nullptr;
    }
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    this->setEndianness(ENDIANNESS::LITTLE);
    _samplesReady=0;

    Header hdr;
    *this >> hdr.signature;
    *this >> hdr.samples;
    *this >> hdr.channels;
    *this >> hdr.rate;

    int16_t tmpword;
    readBytes((char *) &tmpword, 2);
    _subblocks = (int32_t) (tmpword>>4);
    _levels = (int32_t) (tmpword&15);

    if (hdr.signature != IP_ACM_SIG)
    {
        throw Exception("Not an ACM file - invalid signature");
    }

    _samplesLeft = ( _samples = hdr.samples );
    _channels = hdr.channels;
    _bitrate = hdr.rate;
    _blockSize = ( 1 << _levels) * _subblocks;

    _block = (int32_t *) malloc(sizeof(int32_t)* _blockSize);

    _unpacker = std::shared_ptr<ValueUnpacker>(new ValueUnpacker(_levels, _subblocks, this));
    if (!_unpacker || !_unpacker->init())
    {
        throw Exception("Cannot create or init unpacker");
    }
    _decoder = std::shared_ptr<SubbandDecoder>(new SubbandDecoder(_levels));
    if (!_decoder || !_decoder->init())
    {
        throw Exception("Cannot create or init decoder");
    }
}

void File::init()
{
    _initialize();
}

void File::rewind()
{
    Dat::Item::setPosition(0);
    _samplesReady=0;

    Header hdr;
    *this >> hdr.signature;
    *this >> hdr.samples;
    *this >> hdr.channels;
    *this >> hdr.rate;

    int16_t tmpword;
    readBytes((char *) &tmpword, 2);
    _subblocks = (int32_t) (tmpword>>4);
    _levels = (int32_t) (tmpword&15);

    if (hdr.signature != IP_ACM_SIG)
    {
        throw Exception("Not an ACM file - invalid signature");
    }

    _samplesLeft = ( _samples = hdr.samples );
    _channels = hdr.channels;
    _bitrate = hdr.rate;
    _blockSize = ( 1 << _levels) * _subblocks;

    if (_block != nullptr)
    {
        free(_block);
        _block = nullptr;
    }
    _block = (int32_t *) malloc(sizeof(int32_t)* _blockSize);


    _unpacker = std::shared_ptr<ValueUnpacker>(new ValueUnpacker(_levels, _subblocks, this));
    if (!_unpacker || !_unpacker->init())
    {
        throw Exception("Cannot create or init unpacker");
    }
    _decoder = std::shared_ptr<SubbandDecoder>(new SubbandDecoder(_levels));
    if (!_decoder || !_decoder->init())
    {
        throw Exception("Cannot create or init decoder");
    }
}


int32_t File::_makeNewSamples()
{
    if (!_unpacker->getOneBlock(_block))
    {
        // FIXME: is it an error or the end of the stream?
        return 0;
    }
    _decoder->decodeData(_block, _subblocks);
    _values = _block;
    _samplesReady = ( _blockSize > _samplesLeft) ? _samplesLeft : _blockSize;
    _samplesLeft -= _samplesReady;
    return 1;
}

int32_t File::readSamples(short* buffer, int32_t count)
{
    int32_t res = 0;
    while (res < count) {
        if (_samplesReady == 0) {
            if (_samplesLeft == 0)
                break;
            if (!_makeNewSamples())
                break;
        }
        *buffer = ( short ) ( ( *_values) >> _levels);
        _values++;
        buffer++;
        res += 1;
        _samplesReady--;
    }
    return res;
}

int32_t File::samples() const
{
    return _samples;
}

int32_t File::channels() const
{
    return _channels;
}

int32_t File::bitrate() const
{
    return _bitrate;
}

int32_t File::samplesLeft() const
{
    return _samplesLeft;
}

}
}
