cmake_minimum_required(VERSION 3.16)
project(01_du)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES *.cpp *.h)

add_executable(01_du ${SOURCES})