cmake_minimum_required(VERSION 3.16)
project(Dots)

set(CMAKE_CXX_STANDARD 17)

add_executable(Dots main.cpp engine/grid.cpp engine/grid.h engine/block.cpp engine/block.h engine/utils.cpp engine/utils.h)