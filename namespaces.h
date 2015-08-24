/*
    https://github.com/gekomad/ThreadPool
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

#include <string.h>
#include <algorithm>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <sstream>
#include <climits>
#include <fstream>
#include <iostream>

#include <iostream>
#include <chrono>
#include <mutex>
#include <assert.h>

using namespace std::chrono;

using namespace std;


template<typename T>
void _debug(T a) {
    cout << a << " ";
}

template<typename T, typename... Args>
void _debug(T t, Args... args) {
    cout << t << " ";
    _debug(args...);
}

static mutex _CoutSyncMutex;

template<typename T, typename... Args>
void debug(T t, Args... args) {
    lock_guard<mutex> lock1(_CoutSyncMutex);
    nanoseconds ms = duration_cast<nanoseconds>(system_clock::now().time_since_epoch());
    cout << "info string TIME: " << ms.count() << " ";

    _debug(t, args...);
    cout << "\n";
}

#define ASSERT(a) assert(a)
#define ASSERT_RANGE(value, from, to) assert((value)>=(from) && (value)<=(to))
typedef long long unsigned u64;

static const u64 POW2[64] = {0x1ULL, 0x2ULL, 0x4ULL, 0x8ULL, 0x10ULL, 0x20ULL, 0x40ULL, 0x80ULL, 0x100ULL, 0x200ULL,
                             0x400ULL, 0x800ULL, 0x1000ULL, 0x2000ULL, 0x4000ULL, 0x8000ULL, 0x10000ULL, 0x20000ULL,
                             0x40000ULL, 0x80000ULL, 0x100000ULL, 0x200000ULL, 0x400000ULL, 0x800000ULL,
                             0x1000000ULL, 0x2000000ULL, 0x4000000ULL, 0x8000000ULL, 0x10000000ULL, 0x20000000ULL,
                             0x40000000ULL, 0x80000000ULL, 0x100000000ULL, 0x200000000ULL, 0x400000000ULL,
                             0x800000000ULL, 0x1000000000ULL, 0x2000000000ULL, 0x4000000000ULL, 0x8000000000ULL,
                             0x10000000000ULL, 0x20000000000ULL, 0x40000000000ULL, 0x80000000000ULL,
                             0x100000000000ULL, 0x200000000000ULL, 0x400000000000ULL, 0x800000000000ULL,
                             0x1000000000000ULL, 0x2000000000000ULL, 0x4000000000000ULL, 0x8000000000000ULL,
                             0x10000000000000ULL, 0x20000000000000ULL, 0x40000000000000ULL, 0x80000000000000ULL,
                             0x100000000000000ULL, 0x200000000000000ULL, 0x400000000000000ULL, 0x800000000000000ULL,
                             0x1000000000000000ULL, 0x2000000000000000ULL, 0x4000000000000000ULL,
                             0x8000000000000000ULL};
