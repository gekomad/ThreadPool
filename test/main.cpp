/*
    https://github.com/gekomad/BlockingThreadPool
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

//cd test && g++ -pthread -O3 -DDLOG_LEVEL=INFO -std=c++11 *.cpp -o find_prime_number
//./find_prime_number N_THREADS`

using namespace std;

Ttot tot;
const int CHUNK = 30000;

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
    ThreadPool<MyClass> *threadPool = new ThreadPool<MyClass>();
    threadPool->setNthread(nThreads);
    unsigned i = 0;

    tot.count = 0;

    do {
        info(ARRAY_SIZE - i, " to end");
        MyClass &s = threadPool->getNextThread();

        s.init(&tot, i, i + CHUNK, s1);
        i += CHUNK;
        s.start();
    } while (i < ARRAY_SIZE);

    debug("main thread wait for join");
    threadPool->joinAll();
    debug("main thread end");
    delete threadPool;
    debug("threads: ", nThreads, "TOT: ", (int) tot.count);
}

int main(int argc, char *argv[]) {
    cout << "Find first " << ARRAY_SIZE << " prime numbers\n";
    if (argc == 1) {
        cout << "use: " << argv[0] << " N_THREADS\n";
        return 1;
    }
    bool *s1 = (bool *) malloc(sizeof(ARRAY_SIZE) * ARRAY_SIZE);
    assert(s1);

    if (atoi(argv[1]) == 1) {
        info ("single thread..");
        singleThreads(s1);
    } else {
        if (atoi(argv[1]) <= 0 || atoi(argv[1]) > 64) {
            cout << "error. N_THREADS > 0 and <=64 \n";
            return 1;
        }
        info ("multi threads..");
        int nThreads = atoi(argv[1]);
        multiThreads(s1, nThreads);
    }
    string name("first_" + to_string(ARRAY_SIZE) + "_prime_numbers.txt");
    cout << "Found " << tot.count << " prime numbers in " << name << endl;
    std::ofstream fout(name);

    for (int i = 0; i <= ARRAY_SIZE; i++) {
        if (s1[i]) {
            fout << i << ", ";
        }
    }
    fout << std::endl;
    fout.close();
    cout << endl;
    free(s1);

    return 0;
}