//
// Created by void on 5/27/20.
//

#include "grid.h"
#include "utils.h"
#include <stdexcept>
#include <iostream>

grid::grid(int width, int height) {
    this->height = height;
    this->width = width;

    screen.resize(width * height);

    for (int i = 0; i < this->width * this->height; ++i) {
        screen[i] = new block();
    }
}

void grid::render() {

    char chars[5];
    for (int i = 0; i < this->width * this->height; i++) {
        utils::int_to_uchar(screen[i]->to_unicode_char(), chars);

        if (i % this->width == this->width - 1) {
            std::cout << chars << std::endl;
        } else {
            std::cout << chars;
        }
    }
}

int grid::get_width() const {
    return this->width * 2;
}

int grid::get_height() const {
    return this->height * 4;
}

void grid::set(int x, int y) {
    this->check_bounds(x, y);
    modify(x, y, true);
}

void grid::unset(int x, int y) {
    this->check_bounds(x, y);
    modify(x, y, false);
}

void grid::modify(int x, int y, bool value) {
    check_bounds(x, y);
    block *b = screen[((y / 4) * width) + (x / 2)];
    b->modify(x % 2, y % 4, value);
}

void grid::clear() {
    for (int i = 0; i < this->width * this->height; i++) {
        screen[i]->reset();
    }
}

void grid::check_bounds(int x, int y) const {
    if (x >= get_width() || y >= get_height() || x < 0 || y < 0) {
        throw std::out_of_range("Coordinates do not describe a valid position in this grid");
    }
}
