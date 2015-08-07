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
#include "MyClass.h"

//cd test && g++ -pthread -std=c++11 main.cpp MyClass.cpp

using namespace std;

int main() {
    srand(time(NULL));
    int TOT = 100;
    ThreadPool<MyClass> *threadPool = new ThreadPool<MyClass>();
    threadPool->setNthread(4);
    for (int i = 1; i <= TOT; i++) {
        MyClass &s = threadPool->getNextThread();
        debug("main thread -------------------------------", i, "/", TOT);
        s.start();
    }
    debug("main thread wait for join");
    threadPool->joinAll();
    debug("main thread end");
    delete threadPool;
    return 0;
}