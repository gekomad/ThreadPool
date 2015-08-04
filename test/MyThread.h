/*
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

#include "../Thread.h"
#include <iostream>

class MyThread : public Thread {
public:
    MyThread(int i) : Thread(i) { };

    void run() {
        for (int i = 0; i < 2; i++) {
            debug("thread #", getId(), " step ", i, "/", 1);
            sleep(rand() % 5);
        }
    };

    void endRun() {
        debug("thread #", getId(), " terminated");
    }

//    void endThread() {
//        debug("thread #", getId(), " end work");
//    };
};