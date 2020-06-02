cmake_minimum_required(VERSION 3.16)
project(Dots)

set(CMAKE_CXX_STANDARD 17)

add_executable(Dots main.cpp rendering/geometry/line.cpp rendering/geometry/line.h rendering/geometry/triangle.cpp rendering/geometry/triangle.h rendering/geometry/point.cpp rendering/geometry/point.h engine/particle.cpp engine/particle.h rendering/grid.cpp rendering/grid.h)