# ThreadPool
C++11 Thread Pool implementation 

use:

1. your class extends `Thread` and implements `run` and `endRun` methods
2. create threads pool: `ThreadPool<MyClass> threadPool;`
3. get thread if available else wait: `MyClass &myThread = threadPool.getNextThread()`
4. execute `run` method: `myThread.start()`

example:

 `ThreadPool<MyClass> threadPool;`

  `threadPool.setNthread(4);//max 4 running threads`

  `for(int i=0;i<100;i++){`

  `  MyClass &myThread = threadPool.getNextThread();`

  `  myThread.start();`

  `}`

  `threadPool.joinAll();`

```javascript
function fancyAlert(arg) {
  if(arg) {
    $.facebox({div:'#foo'})
  }
}
```

`test` directory contains an example, how to find prime 100000 numbers spreading the work on many threads, to compile:

`cd test && g++ -pthread -O3 -DDLOG_LEVEL=INFO -std=c++11 main.cpp MyClass.cpp -o find_prime_number`

`./find_prime_number N_THREADS`

N_THREADS max 64

