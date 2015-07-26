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