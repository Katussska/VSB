cmake_minimum_required(VERSION 3.16)
project(invoice)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES src/*.cpp src/*.h)

add_executable(invoice.out ${SOURCES})
