/*
    https://github.com/gekomad/BlockingThreadPool
    Copyright (C) Giuseppe Cannella

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "namespaces.h"

class Bits {

public:

#ifdef HAS_POPCNT

    static int bitCount(u64 bits) {
        return __builtin_popcountll(bits);
    }

#else

    static int bitCount(u64 bits) {
        int count = 0;
        while (bits) {
            count++;
            bits &= bits - 1;
        }
        return count;
    }

#endif

    static int BITScanForwardUnset(u64 bb) {
        return BITScanForward(~bb);
    }

#ifdef HAS_BSF
#if UINTPTR_MAX == 0xffffffffffffffff

    static int BITScanForward(u64 bits) {
        return __builtin_ffsll(bits) - 1;
    }

#else
    static int BITScanForward(u64 bits) {
        return ((unsigned) bits) ? __builtin_ffs(bits) - 1 : __builtin_ffs(bits >> 32) + 31;
    }

#endif
#else

    static int BITScanForward(u64 bb) {
        //  @author Matt Taylor (2003)
        static const int lsb_64_table[64] = {63, 30, 3, 32, 59, 14, 11, 33, 60, 24, 50, 9, 55, 19, 21, 34, 61, 29, 2,
                                             53, 51, 23, 41, 18, 56, 28, 1, 43, 46, 27, 0, 35, 62, 31, 58, 4, 5, 49, 54,
                                             6, 15, 52, 12, 40, 7, 42, 45, 16, 25, 57, 48, 13, 10, 39, 8, 44, 20, 47,
                                             38, 22, 17, 37, 36, 26};
        unsigned int folded;
        bb ^= bb - 1;
        folded = (int) bb ^ (bb >> 32);
        return lsb_64_table[folded * 0x78291ACF >> 26];
    }

#endif

};

