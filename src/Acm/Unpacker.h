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

#ifndef LIBFALLTERGEIST_ACM_VALUEUNPACKER_H
#define LIBFALLTERGEIST_ACM_VALUEUNPACKER_H

// C++ standard includes

// libfalltergeist includes
#include "../Dat/Item.h"

// Third party includes

#define UNPACKER_BUFFER_SIZE 16384

namespace libfalltergeist
{
namespace Acm
{

class ValueUnpacker
{

public:

    ValueUnpacker(int levCnt, int sbCount, Dat::Item *stream);
    virtual ~ValueUnpacker();

    // These functions are used to fill the buffer with the amplitude values
    int return0(int pass, int ind);
    int zeroFill(int pass, int ind);
    int linearFill(int pass, int ind);
    int k1_3bits(int pass, int ind);
    int k1_2bits(int pass, int ind);
    int t1_5bits(int pass, int ind);
    int k2_4bits(int pass, int ind);
    int k2_3bits(int pass, int ind);
    int t2_7bits(int pass, int ind);
    int k3_5bits(int pass, int ind);
    int k3_4bits(int pass, int ind);
    int k4_5bits(int pass, int ind);
    int k4_4bits(int pass, int ind);
    int t3_7bits(int pass, int ind);

    int init();
    int getOneBlock(int *block);

protected:
    // Parameters of ACM stream
    int _levels, _subblocks;
    Dat::Item *stream;
    // Bits
    unsigned int _nextBits; // new bits
    int _availBits; // count of new bits
    unsigned char _bitsBuffer[UNPACKER_BUFFER_SIZE];
    unsigned int _bufferBitOffset;

    int _sbSize;
    short *_ampBuffer, *_buffMiddle;
    int *_blockPtr;

    // Reading routines
    void _prepareBits(int bits); // request bits
    int _getBits(int bits); // request and return next bits

};

typedef int (ValueUnpacker::*FillerProc)(int pass, int ind);

}
}
#endif // LIBFALLTERGEIST_ACM_VALUEUNPACKER_H
