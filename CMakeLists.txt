cmake_minimum_required(VERSION 3.3)
project(ThreadPool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -DDEBUG_MODE")

set(SOURCE_FILES
    test/main.cpp
    test/MyClass.cpp
    test/MyClass.h
    Bits.h
    logger.h
    Mutex.h
    namespaces.h
    ObserverThread.h
    Singleton.h
    Thread.h
    ThreadPool.h)

add_executable(ThreadPool ${SOURCE_FILES})