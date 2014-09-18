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

#ifndef LIBFALLTERGEIST_ACMFILETYPE_H
#define LIBFALLTERGEIST_ACMFILETYPE_H

// C++ standard includes

// libfalltergeist includes
#include "../src/DatFileItem.h"
#include "unpacker.h"
#include "decoder.h"

namespace libfalltergeist
{

class AcmFileType : public DatFileItem
{
private:
    int samples_left; // count of unread samples
    int levels, subblocks;
    int block_size;
    int* block, * values;
    int samples_ready;
    std::shared_ptr<CValueUnpacker> unpacker; // ACM-stream unpacker
    std::shared_ptr<CSubbandDecoder> decoder; // IP's subband decoder
    int _samples; // total count of sound samples
    int _channels;
    int _bitrate;
    int make_new_samples();

protected:
    virtual void _initialize();
public:
    AcmFileType(std::shared_ptr<DatFileEntry> datFileEntry);
    AcmFileType(std::ifstream* stream);
    ~AcmFileType();
    void init();

    int samples() const;
    int channels() const;
    int bitrate() const;

    int read_samples(short* buffer, int count);
};

}
#endif // LIBFALLTERGEIST_ACMFILETYPE_H
