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

#ifndef LIBFALLTERGEIST_ACM_FILE_H
#define LIBFALLTERGEIST_ACM_FILE_H

// C++ standard includes

// libfalltergeist includes

#include "../Dat/Item.h"

namespace libfalltergeist
{
namespace Acm
{

class ValueUnpacker;
class SubbandDecoder;

class File : public Dat::Item
{

public:
    File(std::shared_ptr<Dat::Entry> datFileEntry);
    File(std::ifstream* stream);
    ~File();
    void init();
    void rewind();

    int samples() const;
    int channels() const;
    int bitrate() const;

    int readSamples(short* buffer, int count);

    int samplesLeft() const;

protected:
    virtual void _initialize();
    int _samplesLeft; // count of unread samples
    int _levels, _subblocks;
    int _blockSize;
    int* _block = nullptr;
    int* _values = nullptr;
    int _samplesReady;
    std::shared_ptr<ValueUnpacker> _unpacker; // ACM-stream unpacker
    std::shared_ptr<SubbandDecoder> _decoder; // IP's subband decoder
    int _samples; // total count of sound samples
    int _channels;
    int _bitrate;
    int _makeNewSamples();

};

}
}
#endif // LIBFALLTERGEIST_ACM_FILE_H
