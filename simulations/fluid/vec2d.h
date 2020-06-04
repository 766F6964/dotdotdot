//
// Created by void on 6/3/20.
//

#ifndef DOTS_VEC2D_H
#define DOTS_VEC2D_H

// https://codereview.stackexchange.com/questions/26608/review-of-2d-vector-class

class vec2d {
public:

    float x;
    float y;

    vec2d();

    vec2d(float x, float y);

    vec2d operator+(const vec2d &) const;

    vec2d operator-(const vec2d &) const;

    vec2d operator*(const vec2d &) const;

    vec2d operator/(const vec2d &) const;

    bool operator==(const vec2d &) const;

    bool operator>(const vec2d &) const;

    bool operator<(const vec2d &) const;

    bool operator>=(const vec2d &) const;

    bool operator<=(const vec2d &) const;

    vec2d operator*(const float &) const;

    vec2d operator/(const float &) const;

private:


};


#endif //DOTS_VEC2D_H
