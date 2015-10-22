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


#include "MyClass.h"

void MyClass::run() {
    info("run thread #", getId());

    found = 0;
    for (int i = from; i <= to; i++) {
        s1[i] = isPrime(i);
        if (s1[i])found++;
    }
}

void MyClass::endRun() {
    info("endRun thread #", getId(), " found: ", found);
    mainTot->count += found;
}

void MyClass::init(Ttot *mainTot, unsigned from, unsigned to, bool *s1) {

    this->mainTot = mainTot;
    this->from = from;
    this->to = std::min(to, ARRAY_SIZE);
    this->s1 = s1;

    found = 0;
}
