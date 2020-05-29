cmake_minimum_required(VERSION 3.16)
project(Dots)

set(CMAKE_CXX_STANDARD 17)

add_executable(Dots main.cpp engine/grid.cpp engine/grid.h engine/block.cpp engine/block.h engine/utils.cpp engine/utils.h engine/geometry/line.cpp engine/geometry/line.h engine/geometry/triangle.cpp engine/geometry/triangle.h engine/geometry/point.cpp engine/geometry/point.h examples/examples.cpp examples/examples.h)