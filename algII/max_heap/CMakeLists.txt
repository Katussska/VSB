cmake_minimum_required(VERSION 3.24)
project(max_heap)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES src/*.cpp src/*.h src/*/*.cpp src/*/*.h)

add_executable(${CMAKE_PROJECT_NAME}.out ${SOURCES}
        src/MaxHeap.h)