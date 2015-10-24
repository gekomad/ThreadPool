/*
    https://github.com/gekomad/Auriga
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

#include "../util/Singleton.h"

using namespace std;

#if !defined DLOG_LEVEL
#if defined DEBUG_MODE
#define DLOG_LEVEL TRACE
#else
#define DLOG_LEVEL OFF
#endif
#endif

namespace _logger {

    static enum LOG_LEVEL {
        TRACE = 0, DEBUG = 1, INFO = 2, WARN = 3, ERROR = 4, FATAL = 5, OFF = 6, ALWAYS = 7
    } _LOG_LEVEL;

    static const string LOG_LEVEL_STRING[] = {"TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL", "OFF", "LOG"};

    class Logger : public Singleton<Logger>, public ofstream {
        friend class Singleton<Logger>;

    public:
        void setLogfile(const string &f, const bool append = false) {
            this->open(f, append ? std::ofstream::app : std::ofstream::out);
        }

        template<LOG_LEVEL type, typename T, typename... Args>
        void _log(T t, Args... args) {
            lock_guard<mutex> lock1(_CoutSyncMutex);
            cout << Time::getLocalTime() << " " << LOG_LEVEL_STRING[type] << " ";
            *this << Time::getLocalTime() << " " << LOG_LEVEL_STRING[type] << " ";
            __log(t, args...);
            cout << endl;
            *this << endl;
        }

    private:
        mutex _CoutSyncMutex;

        template<typename T>
        void __log(T t) {
            cout << (t);
            *this << (t);
        }

        template<typename T, typename... Args>
        void __log(T t, Args... args) {
            cout << (t);
            *this << (t);
            __log(args...);
        }

        ~Logger() {
            this->close();
        }
    };

    static Logger &logger = Logger::getInstance();

#if defined(_WIN32)
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define LINE_INFO __FILENAME__,":",__LINE__," "

#define log(...)                            {logger._log<LOG_LEVEL::ALWAYS>(LINE_INFO,__VA_ARGS__);}
#define trace(...) if (TRACE >= DLOG_LEVEL) {logger._log<LOG_LEVEL::TRACE>( LINE_INFO,__VA_ARGS__);}
#define debug(...) if (DEBUG >= DLOG_LEVEL) {logger._log<LOG_LEVEL::DEBUG>( LINE_INFO,__VA_ARGS__);}
#define info(...)  if (INFO  >= DLOG_LEVEL) {logger._log<LOG_LEVEL::INFO> ( LINE_INFO,__VA_ARGS__);}
#define warn(...)  if (WARN  >= DLOG_LEVEL) {logger._log<LOG_LEVEL::WARN> ( LINE_INFO,__VA_ARGS__);}
#define error(...) if (ERROR >= DLOG_LEVEL) {logger._log<LOG_LEVEL::ERROR>( LINE_INFO,__VA_ARGS__);}
#define fatal(...) if (FATAL >= DLOG_LEVEL) {logger._log<LOG_LEVEL::FATAL>( LINE_INFO,__VA_ARGS__);}

}
