//
// Created by void on 6/3/20.
//

#include "vec2d.h"


vec2d::vec2d() {
    this->x = 0.0f;
    this->y = 0.0f;
}

vec2d::vec2d(float x, float y) {
    this->x = x;
    this->y = y;
}

vec2d vec2d::operator+(const vec2d &v) const {
    return {x + v.x, y + v.y};
}

vec2d vec2d::operator/(const vec2d &v) const {
    return {x / v.x, y / v.y};
}

vec2d vec2d::operator*(const vec2d &v) const {
    return {x * v.x, y * v.y};
}

vec2d vec2d::operator-(const vec2d &v) const {
    return {x - v.x, y - v.y};
}

bool vec2d::operator==(const vec2d &v) const {
    return ((v.x == x) && (v.y == y));
}

bool vec2d::operator>(const vec2d &v) const {
    return (x * x + y * y) > (v.x * v.x + v.y * v.y);
}

bool vec2d::operator<(const vec2d &v) const {
    return (x * x + y * y) < (v.x * v.x + v.y * v.y);
}

bool vec2d::operator>=(const vec2d &v) const {
    return (x * x + y * y) > (v.x * v.x + v.y * v.y) ||
           (x * x + y * y) == (v.x * v.x + v.y * v.y);
}

bool vec2d::operator<=(const vec2d &v) const {
    return (x * x + y * y) < (v.x * v.x + v.y * v.y) ||
           (x * x + y * y) == (v.x * v.x + v.y * v.y);
}

vec2d vec2d::operator*(const float &scalar) const {
    return {x * scalar, y * scalar};
}

vec2d vec2d::operator/(const float &scalar) const {
    return {x / scalar, y / scalar};
}
