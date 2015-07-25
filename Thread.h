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

#include <thread>
#include <mutex>
#include "ObserverThread.h"

using namespace std;

class Runnable {
public:
    virtual void run() = 0;

    virtual void endThread() = 0;
};

class Thread : virtual public Runnable {

private:

    int threadID = -1;
    ObserverThread *observer = nullptr;
    thread theThread;

    Runnable *execRunnable;

    static void *__run(void *cthis) {
        static_cast<Runnable *>(cthis)->run();
        static_cast<Runnable *>(cthis)->endThread();
        static_cast<Thread *>(cthis)->notifyEndThread((static_cast<Thread *>(cthis))->getId());

        return nullptr;
    }

public:
    void registerObserverThread(ObserverThread *obs) {
        observer = obs;
    }

    void notifyEndThread(int threadID) {
        observer->observerEndThread(threadID);
    }

    Thread() {
        execRunnable = this;
    }

    void start() {
        join();
        theThread = thread(__run, execRunnable);
    }

    void join() {
        if (theThread.joinable()) {
            theThread.join();
        }
    }

    int getId() const {
        return threadID;
    }

    void setId(int threadID) {
        Thread::threadID = threadID;
    }
};
