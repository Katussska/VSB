cmake_minimum_required(VERSION 3.16)
project(binaryTree)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES *.cpp *.h *.txt)

add_executable(binaryTree ${SOURCES})