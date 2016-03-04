
project(ThreadPool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -DDEBUG_MODE")

set(SOURCE_FILES
    test/main.cpp
    test/MyClass.cpp
    util/String.cpp
   )

add_executable(ThreadPool ${SOURCE_FILES})