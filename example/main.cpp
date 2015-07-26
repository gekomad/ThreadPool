#include <iostream>
#include "../ThreadPool.h"
#include "MyThread.h"

using namespace std;

int main() {
    int activeThread = 2;
    ThreadPool<MyThread> threadPool(activeThread);
    for (int i = 0; i < 10; i++) {
        MyThread &s = threadPool.getNextThread();
        cout << "main thread -------------------------------" << i << "/" << 10 << endl;
        threadPool.startThread(s);
    }
    cout << "main thread wait for join\n";
    threadPool.joinAll();
    cout << "main thread end\n";
    return 0;
}