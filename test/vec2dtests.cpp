//
// Created by void on 6/7/20.
//

#include "gtest/gtest.h"
#include "../src/simulations/fluid/vec2d.h"

TEST(vector_tests, vector_addition_test) {
    vec2d v1(10, 20);
    vec2d v2(10, 20);

    vec2d v3(20, 40);
    EXPECT_EQ(v1 + v2, v3);
}

TEST(vector_tests, vector_subtraction_test) {
    vec2d v1(10, 60);
    vec2d v2(70, 35);

    vec2d v3(-60, 25);
    EXPECT_EQ(v1 - v2, v3);
}

TEST(vector_tests, vector_multiply_test) {
    vec2d v1(15, 7);
    vec2d v2(-10, 30);

    vec2d v3(-150, 210);
    EXPECT_EQ(v1 * v2, v3);
}

TEST(vector_tests, vector_divide_test) {
    vec2d v1(100, 100);
    vec2d v2(50, 70);

    vec2d v3(2, 1.4285714285714286);
    EXPECT_EQ(v1 / v2, v3);
}

TEST(vector_tests, vector_eq_test) {
    vec2d v1(10, 20);
    vec2d v2(10, 20);
    vec2d v3(20, 40);
    EXPECT_EQ(v1 == v2, true);
    EXPECT_EQ(v2 == v3, false);
}

TEST(vector_tests, vector_geq_test) {
    vec2d v1(10, 20);
    vec2d v2(10, 20);
    vec2d v3(20, 40);
    EXPECT_EQ(v1 >= v2, true);
    EXPECT_EQ(v3 >= v2, true);
    EXPECT_EQ(v1 >= v3, false);
}

TEST(vector_tests, vector_leq_test) {
    vec2d v1(10, 20);
    vec2d v2(10, 20);
    vec2d v3(20, 40);
    EXPECT_EQ(v1 <= v2, true);
    EXPECT_EQ(v1 <= v3, true);
    EXPECT_EQ(v3 <= v2, false);
}

TEST(vector_tests, vector_greater_test) {
    vec2d v1(10, 20);
    vec2d v2(10, 20);
    vec2d v3(20, 40);
    EXPECT_EQ(v1 > v2, false);
    EXPECT_EQ(v3 > v2, true);
    EXPECT_EQ(v1 > v3, false);
}

TEST(vector_tests, vector_less_test) {
    vec2d v1(10, 20);
    vec2d v2(10, 20);
    vec2d v3(20, 40);
    EXPECT_EQ(v1 < v2, false);
    EXPECT_EQ(v1 < v3, true);
    EXPECT_EQ(v3 < v2, false);
}

TEST(vector_tests, vector_scalar_multiply_test) {
    vec2d v1(10, 20);
    int scalar = 5;

    vec2d v2(50, 100);
    EXPECT_EQ(v1 * scalar, v2);
}

TEST(vector_tests, vector_scalar_divide_test) {
    vec2d v1(10, 20);
    int scalar = 40;

    vec2d v2(0.25, 0.5);
    EXPECT_EQ(v1 / scalar, v2);
}