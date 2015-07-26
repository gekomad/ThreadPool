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
#include <vector>
#include <unistd.h>
#include "ObserverThread.h"
#include <math.h>
#include "ConditionVariable.h"
#include <bitset>
#include <assert.h>
#include "Thread.h"
#include "CoutSync.h"

using namespace std;


template<typename T, typename = typename std::enable_if<std::is_base_of<Thread, T>::value, T>::type>
class ThreadPool : virtual public ObserverThread {

public:
    static const int MAX_THREAD = 128;

    ThreadPool(int n) : nThread(n) {
        assert(n < MAX_THREAD);
        if (thread::hardware_concurrency() && nThread > thread::hardware_concurrency()) {
            CoutSync() << "WARNING active threads (" << nThread << ") > physical cores (" << thread::hardware_concurrency() << ")\n";
        }
        for (int i = 0; i < n; i++) {
            T *x = new T(i);
            x->registerObserverThread(this);
            threadPool.push_back(x);
        }
    }

    T &getNextThread() {
        lock_guard<mutex> lock1(mx);
        if (threadsBits.count() == nThread) {
            cv.wait();
        }
        int i;
        for (i = 0; i < nThread; i++) {
            if (threadsBits[i] == 0)break;
        }
        assert(i != nThread);
        threadsBits[i] = 1;
        return *threadPool[i];
    }

    void observerEndThread(int threadID) {
        releaseThread(threadID);
    }

    void joinAll() {
       for(T* s:threadPool){
           s->join();
       }
    }

    void startThread(T &thread) {
        thread.start();
    }

    ~ThreadPool() {
        destroy();
    }

protected:
    vector<T *> threadPool;

private:
    mutex mx;
    mutex mx1;

    bitset<MAX_THREAD> threadsBits = 0;

    int nThread;
    ConditionVariable cv;

    void releaseThread(int threadID) {
        lock_guard<mutex> lock1(mx1);
        threadsBits[threadID] = 0;
        cv.notifyOne();
    }

    void destroy() {
        for (unsigned i = 0; i < threadPool.size(); i++) {
            delete threadPool[i];
        }
        threadPool.clear();
    }

};


