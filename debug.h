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

#include <mutex>
#include <cxxabi.h>
#include <stdio.h>
#include <string>
#include<iostream>
#include <chrono>
#include <algorithm>

using namespace std::chrono;
using namespace std;

enum LOG_LEVEL {
    TRACE = 0, DEBUG = 1, INFO = 2, WARN = 3, ERROR = 4, FATAL = 5, OFF = 6
};

#if !defined DLOG_LEVEL
#if defined DEBUG_MODE
#define DLOG_LEVEL TRACE
#else
#define DLOG_LEVEL OFF
#endif
#endif

namespace _debug {


    static const std::string LOG_LEVEL_STRING[7] = {"TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL", "OFF"};

#if defined(_WIN32)
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define LINE_INFO __FILENAME__,":",__LINE__," "

    template<typename T>
    void __log(T a) {
        cout << (a);
    }

    template<typename T, typename... Args>
    void __log(T t, Args... args) {
        cout << t;
        __log(args...);
    }

    static mutex _CoutSyncMutex;

    template<LOG_LEVEL type, typename T, typename... Args>
    void _log(T t, Args... args) {
        lock_guard<mutex> lock1(_CoutSyncMutex);
//        nanoseconds ms = duration_cast<nanoseconds>(system_clock::now().time_since_epoch());
//        cout << ">>" << LOG_LEVEL_STRING[type] << " nanoseconds:" << ms.count() << " ";

        time_t current = chrono::system_clock::to_time_t(chrono::system_clock::now());
        string now = (ctime(&current));
        now.erase(find_if(now.rbegin(), now.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), now.end());
        cout << LOG_LEVEL_STRING[type] << " " << now << " ";

        __log(t, args...);
        cout << endl;
    }

#define trace(...) if (LOG_LEVEL::TRACE >= DLOG_LEVEL) {_debug::_log<LOG_LEVEL::TRACE>( LINE_INFO,__VA_ARGS__);}
#define debug(...) if (LOG_LEVEL::DEBUG >= DLOG_LEVEL) {_debug::_log<LOG_LEVEL::DEBUG>( LINE_INFO,__VA_ARGS__);}
#define info(...)  if (LOG_LEVEL::INFO  >= DLOG_LEVEL) {_debug::_log<LOG_LEVEL::INFO> ( LINE_INFO,__VA_ARGS__);}
#define warn(...)  if (LOG_LEVEL::WARN  >= DLOG_LEVEL) {_debug::_log<LOG_LEVEL::WARN> ( LINE_INFO,__VA_ARGS__);}
#define error(...) if (LOG_LEVEL::ERROR >= DLOG_LEVEL) {_debug::_log<LOG_LEVEL::ERROR>( LINE_INFO,__VA_ARGS__);}
#define fatal(...) if (LOG_LEVEL::FATAL >= DLOG_LEVEL) {_debug::_log<LOG_LEVEL::FATAL>( LINE_INFO,__VA_ARGS__);}

}