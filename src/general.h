// DISCLAIMER.
// This code was taken from the ACMReader plugin of the GemRB project (http://gemrb.org)
// and then adapted for libfalltergeist. All credit goes to the original authors.

#ifndef _ACM_LAB_GENERAL_H
#define _ACM_LAB_GENERAL_H

// Interplay ACM signature
#define IP_ACM_SIG 0x01032897

struct ACM_Header {
    unsigned int signature;
    unsigned int samples;
    unsigned short channels;
    unsigned short rate;
    unsigned short levels : 4;
    unsigned short subblocks : 12;
};

#endif
