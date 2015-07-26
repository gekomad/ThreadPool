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

#include <iostream>
#include "../ThreadPool.h"
#include "MyThread.h"
#include "../CoutSync.h"

using namespace std;

int main() {
    int activeThread = 2;
    ThreadPool<MyThread> threadPool(activeThread);
    for (int i = 1; i <= 10; i++) {
        MyThread &s = threadPool.getNextThread();
        CoutSync() << "main thread -------------------------------" << i << "/" << 10;
        threadPool.startThread(s);
    }
    CoutSync() << "main thread wait for join";
    threadPool.joinAll();
    CoutSync() << "main thread end";
    return 0;
}