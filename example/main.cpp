#include <iostream>
#include "../ThreadPool.h"
#include "MyThread.h"

using namespace std;

int main() {

    ThreadPool<MyThread> threadPool(16);
    for (int i = 0; i < 1000; i++) {
        cout << "main step " << i << "/" << 100 << endl;

        MyThread &s = threadPool.getNextThread();

        threadPool.startThread(s);
    }
    cout << "end" << endl;
    return 0;
}