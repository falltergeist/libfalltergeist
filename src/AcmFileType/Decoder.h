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

#ifndef LIBFALLTERGEIST_ACM_SUBBAND_DECODER_H
#define LIBFALLTERGEIST_ACM_SUBBAND_DECODER_H

#include <cstdlib>

namespace libfalltergeist
{

class CSubbandDecoder
{
private:
    int _levels, _blockSize;
    int *_memoryBuffer;

    void _sub4d3fcc(short *memory, int *buffer, int sbSize, int blocks);

    void _sub4d420c(int *memory, int *buffer, int sbSize, int blocks);

public:
    CSubbandDecoder(int lev_cnt);

    virtual ~CSubbandDecoder();

    int init();

    void decodeData(int *buffer, int blocks);
};

}

#endif // LIBFALLTERGEIST_ACM_SUBBAND_DECODER_H
