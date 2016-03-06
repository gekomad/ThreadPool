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

#include <iostream>
#include "../ThreadPool.h"
#include "MyClass.h"

using namespace std;

Ttot tot;
const int CHUNK = 3000;

void singleThreads(bool *s1) {
    unsigned tot = 0;
    for (int i = 0; i <= ARRAY_SIZE; i++) {
        if (i % CHUNK == 0) info(ARRAY_SIZE - i, " to end");
        s1[i] = MyClass::isPrime(i);
        if (s1[i])tot++;
    }
    debug("single thread TOT: ", tot);
}

void multiThreads(bool *s1, int nThreads) {
    ThreadPool<MyClass> threadPool;
    threadPool.setNthread(nThreads);
    unsigned i = 0;

    tot.count = 0;

    do {
        info(ARRAY_SIZE - i, " to end");
        MyClass &s = threadPool.getNextThread();

        s.init(&tot, i, i + CHUNK, s1);
        i += CHUNK;
        s.start();
    } while (i < ARRAY_SIZE);

    debug("main thread wait for join");
    threadPool.joinAll();
    debug("main thread end");
    debug("threads: ", nThreads, "TOT: ", (int) tot.count);
}

static unsigned diffTime(high_resolution_clock::time_point t1, high_resolution_clock::time_point t2) {
    std::chrono::duration<double, std::milli> elapsed = t1 - t2;
    return elapsed.count();
}

int main(int argc, char *argv[]) {
    cout << "Find prime numbers from 0 to " << ARRAY_SIZE << endl;
    if (argc == 1) {
        cout << "use: " << argv[0] << " N_THREADS\n";
        return 1;
    }
    bool *s1 = (bool *) malloc(sizeof(ARRAY_SIZE) * ARRAY_SIZE);
    assert(s1);
    unsigned millsec;
    if (atoi(argv[1]) == 1) {
        info ("single thread..");
        auto start = std::chrono::high_resolution_clock::now();
        singleThreads(s1);
        auto end = std::chrono::high_resolution_clock::now();
        millsec = diffTime(end, start);
    } else {
        if (atoi(argv[1]) <= 0 || atoi(argv[1]) > 64) {
            cout << "error. N_THREADS > 0 and <=64 \n";
            return 1;
        }

        info ("multi threads..");
        int nThreads = atoi(argv[1]);
        auto start = std::chrono::high_resolution_clock::now();
        multiThreads(s1, nThreads);
        auto end = std::chrono::high_resolution_clock::now();
        millsec = diffTime(end, start);
    }
    string name("prime_numbers.txt");
    cout << "\nTime " << millsec << " millsec output in " << name << endl;
    std::ofstream fout(name);

    for (int i = 0; i <= ARRAY_SIZE; i++) {
        if (s1[i]) {
            fout << i << "\n";
        }
    }
    fout << std::endl;
    fout.close();
    cout << endl;
    free(s1);

    return 0;
}
