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

#ifndef LIBFALLTERGEIST_ACM_GENERAL_H
#define LIBFALLTERGEIST_ACM_GENERAL_H

// Interplay ACM signature
#define IP_ACM_SIG 0x01032897

namespace libfalltergeist
{

struct AcmHeader
{
    unsigned int signature;
    unsigned int samples;
    unsigned short channels;
    unsigned short rate;
    unsigned short levels : 4;
    unsigned short subblocks : 12;
};

}

#endif // LIBFALLTERGEIST_ACM_GENERAL_H
