cmake_minimum_required(VERSION 3.2)
project(ThreadPool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

set(SOURCE_FILES
    test/main.cpp
    test/MyClass.h
    test/MyClass.cpp
    namespaces.h
    ObserverThread.h
    Thread.h
    ThreadPool.h)

add_executable(ThreadPool ${SOURCE_FILES})