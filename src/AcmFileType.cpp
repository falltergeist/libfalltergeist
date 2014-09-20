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

// DISCLAIMER.
// This code was taken from the ACMReader plugin of the GemRB project (http://gemrb.org)
// and then adapted for libfalltergeist. All credit goes to the original authors.
// Link to the plugin: https://github.com/gemrb/gemrb/tree/8e759bc6874a80d4a8d73bf79603624465b3aeb0/gemrb/plugins/ACMReader

// C++ standard includes

// libfalltergeist includes
#include "../src/AcmFileType.h"
#include "../src/AcmFileType/Decoder.h"
#include "../src/AcmFileType/General.h"
#include "../src/AcmFileType/Unpacker.h"
#include "../src/Exception.h"

// Third party includes

namespace libfalltergeist
{

AcmFileType::AcmFileType(std::shared_ptr<DatFileEntry> datFileEntry)
        : DatFileItem(datFileEntry), _block(nullptr)
{
}

AcmFileType::AcmFileType(std::ifstream* stream)
        : DatFileItem(stream), _block(nullptr)
{
}

AcmFileType::~AcmFileType()
{
    if (_block != nullptr)
    {
        free(_block);
        _block = nullptr;
    }
}

void AcmFileType::_initialize()
{
    if (_initialized) return;
    this->setEndianness(ENDIANNESS_LITTLE);


    DatFileItem::_initialize();
    DatFileItem::setPosition(0);

    AcmHeader hdr;
    *this >> hdr.signature;
    *this >> hdr.samples;
    *this >> hdr.channels;
    *this >> hdr.rate;

    int16_t tmpword;
    readBytes((char *) &tmpword, 2);
    _subblocks = (int) (tmpword>>4);
    _levels = (int) (tmpword&15);

    if (hdr.signature != IP_ACM_SIG)
    {
        throw Exception("Not an ACM file - invalid signature");
    }

    _samplesLeft = ( _samples = hdr.samples );
    _channels = hdr.channels;
    _bitrate = hdr.rate;
    _blockSize = ( 1 << _levels) * _subblocks;

    _block = (int *) malloc(sizeof(int)* _blockSize);

    _unpacker = std::shared_ptr<CValueUnpacker>(new CValueUnpacker(_levels, _subblocks, this));
    if (!_unpacker || !_unpacker->init())
    {
        throw Exception("Cannot create or init unpacker");
    }
    _decoder = std::shared_ptr<CSubbandDecoder>(new CSubbandDecoder(_levels));
    if (!_decoder || !_decoder->init())
    {
        throw Exception("Cannot create or init decoder");
    }
}

void AcmFileType::init()
{
    _initialize();
}


int AcmFileType::_makeNewSamples()
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

int AcmFileType::readSamples(short* buffer, int count)
{
    int res = 0;
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

int AcmFileType::samplesLeft() const
{
    return _samplesLeft;
}
}
