cmake_minimum_required(VERSION 3.16)
project(library)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES main.cpp src/*.cpp src/*.h src/*/*.cpp src/*/*.h)

add_executable(library ${SOURCES})