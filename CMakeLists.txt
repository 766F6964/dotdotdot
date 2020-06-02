cmake_minimum_required(VERSION 3.16)
project(Dots)

set(CMAKE_CXX_STANDARD 17)

add_executable(Dots main.cpp rendering/utils.cpp rendering/utils.h geometry/line.cpp geometry/line.h geometry/triangle.cpp geometry/triangle.h geometry/point.cpp geometry/point.h examples/examples.cpp examples/examples.h engine/particle.cpp engine/particle.h rendering/grid.cpp rendering/grid.h)