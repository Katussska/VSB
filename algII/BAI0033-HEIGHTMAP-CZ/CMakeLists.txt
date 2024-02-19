cmake_minimum_required(VERSION 3.23)
project(BAI0033_ALG_II)

set(CMAKE_CXX_STANDARD 23)

add_executable(BAI0033_ALG_II main.cpp Column.cpp Column.h HeightMap.cpp HeightMap.h Sides.cpp Sides.h
        Faces_enum.h
        Axis_enum.h)
