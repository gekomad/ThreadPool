/*
    Cinnamon UCI chess engine
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
    cout << endl;
}

#define assert(a) if(!(a)){  cout<<dec<<endl<<" ********************************** assert error in "<< " line "<<__LINE__<<" "<<" **********************************"<<endl;cerr<<flush;exit(1);};
#define ASSERT(a) assert(a)
typedef unsigned char uchar;
static const int POW2[9] = {0x1ULL, 0x2ULL, 0x4ULL, 0x8ULL, 0x10ULL, 0x20ULL, 0x40ULL, 0x80ULL, 0x100ULL};

