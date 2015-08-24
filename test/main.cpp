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

// cd test && g++ -pthread -O3 -std=c++11 *.cpp -o find_prime_number
// ./find_prime_number N_THREADS

using namespace std;

Ttot tot;

void noThreads(bool *s1) {
    unsigned tot = 0;
    for (int i = 0; i <= ARRAY_SIZE; i++) {
        s1[i] = MyClass::isPrime(i);
        if (s1[i])tot++;
    }

    debug("no thread TOT: ", tot);

}

void threads(bool *s1, int nThreads) {
    ThreadPool<MyClass> *threadPool = new ThreadPool<MyClass>();
    threadPool->setNthread(nThreads);
    unsigned i = 0;

    tot.count = 0;
    int chunk = 10000;
    do {

        MyClass &s = threadPool->getNextThread();

        s.init(&tot, i, i + chunk, s1);
        i += chunk;
        s.start();
    } while (i < ARRAY_SIZE);

    debug("main thread wait for join");
    threadPool->joinAll();
    debug("main thread end");
    delete threadPool;
    debug("thread: ", nThreads, "TOT: ", (int) tot.count);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        cout << "error, missing n threads\n";
        return 1;
    }
    bool *s1 = (bool *) malloc(sizeof(ARRAY_SIZE) * ARRAY_SIZE);
    assert(s1);

    if (atoi(argv[1]) == 1) {
        noThreads(s1);
    } else {
        int nThreads = atoi(argv[1]);
        threads(s1, nThreads);
    }
    string name("first_" + to_string(tot.count) + "_prime_numbers.txt");
    cout << "Found " << tot.count << " prime numbers\nWrite in " << name << endl;
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