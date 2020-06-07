cmake_minimum_required(VERSION 3.16)
project(tests)

add_executable(tests
        ../src/simulations/fluid/vec2d.cpp
        gtest.cpp vec2dtests.cpp)
target_link_libraries(tests gtest)