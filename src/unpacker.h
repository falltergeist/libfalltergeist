// DISCLAIMER.
// This code was taken from the ACMReader plugin of the GemRB project (http://gemrb.org)
// and then adapted for libfalltergeist. All credit goes to the original authors.

#ifndef _ACM_LAB_VALUE_UNPACKER_H
#define _ACM_LAB_VALUE_UNPACKER_H

#include <cstdlib>
#include "../src/DatFileItem.h"

#define UNPACKER_BUFFER_SIZE 16384

class CValueUnpacker {
private:
    // Parameters of ACM stream
    int levels, subblocks;
    //FILE* file;
    libfalltergeist::DatFileItem* stream;
    // Bits
    unsigned int next_bits; // new bits
    int avail_bits; // count of new bits
    unsigned char bits_buffer[UNPACKER_BUFFER_SIZE];
    unsigned int buffer_bit_offset;

    int sb_size;
    short* amp_buffer, * buff_middle;
    int* block_ptr;

    // Reading routines
    void prepare_bits(int bits); // request bits
    int get_bits(int bits); // request and return next bits
public:
    // These functions are used to fill the buffer with the amplitude values
    int return0(int pass, int ind);
    int zero_fill(int pass, int ind);
    int linear_fill(int pass, int ind);

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


    CValueUnpacker(int lev_cnt, int sb_count, libfalltergeist::DatFileItem* stream)
            : levels( lev_cnt ), subblocks( sb_count ), next_bits( 0 ),
              avail_bits( 0 ), buffer_bit_offset( UNPACKER_BUFFER_SIZE ),
              sb_size( 1 << levels ),
              amp_buffer(nullptr ),
              buff_middle( nullptr ), block_ptr( nullptr )
    {
        this->stream = stream;
    }
    virtual ~CValueUnpacker()
    {
        if (amp_buffer) {
            free(amp_buffer);
            amp_buffer = nullptr;
        }
    }

    int init_unpacker();
    int get_one_block(int* block);
};

typedef int (CValueUnpacker::*FillerProc) (int pass, int ind);

#endif
