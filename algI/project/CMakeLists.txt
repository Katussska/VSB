cmake_minimum_required(VERSION 3.16)
project(project)

set(CMAKE_CXX_STANDARD 20)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

file(GLOB SOURCES main.cpp src/*.cpp src/*.h src/*/*.cpp src/*/*.h)

add_executable(project ${SOURCES})