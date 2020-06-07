//
// Created by void on 5/29/20.
//

#include "point.h"

point::point(int x, int y) {
    this->x_coord = x;
    this->y_coord = y;
}

int point::get_x() {
    return this->x_coord;
}

int point::get_y() {
    return this->y_coord;
}
