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

#pragma once
#include "../debug.h"
#include "../Thread.h"
#include <iostream>
#include <unistd.h>
#include <atomic>

static const unsigned ARRAY_SIZE = 100000;

typedef struct {
    atomic_int count;
} Ttot;

class MyClass : public Thread {
public:

    virtual void run();

    void init(Ttot *mainTot, unsigned from, unsigned to, bool *s1);

    virtual void endRun();

    static bool isPrime(int number) {
        int count = 0;
        for (int a = 1; a <= number; a++) {
            if (number % a == 0) {
                count++;
            }
        }
        if (count == 2) {
            return true;
        }
        else {
            return false;
        }
    }

private:

    Ttot *mainTot;
    u64 found = 0;

    unsigned from;
    unsigned to;
    bool *s1;

};