# ThreadPool
C++11 Thread Pool implementation 

use:

1. in your class extends `Thread` and implements `run` and `endRun` methods
2. create threads pool: `ThreadPool<MyClass> *threadPool = new ThreadPool<MyClass>()`
3. set threads size in pool (optional): `threadPool->setNthread(nThreads)`
4. return thread if available else wait: `MyClass &myThread = threadPool->getNextThread()`
5. execute `run` method: `myThread.start()`


`test` directory contains an example, how to find prime numbers spreading the work in many threads, to compile:

`cd test && g++ -pthread -O3 -std=c++11 *.cpp -o find_prime_number`

`./find_prime_number N_THREADS`

N_THREADS max 64

