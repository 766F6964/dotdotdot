//
// Created by void on 5/27/20.
//

#include <stdexcept>
#include "cell.h"

cell::cell() {
    reset();
}

void cell::check_bounds(int x, int y) {
    if (x < 0 || y < 0 || x > 1 || y > 3) {
        throw std::out_of_range("Coordinates do not describe a valid position in this cell");
    }
}

void cell::set(int x, int y) {
    modify(x, y, true);
}

void cell::unset(int x, int y) {
    modify(x, y, false);
}

bool cell::is_set(int x, int y) {
    check_bounds(x, y);
    return block_map[y * 2 + x];
}

void cell::modify(int x, int y, bool value) {
    check_bounds(x, y);
    block_map[y * 2 + x] = value;
}

int cell::to_unicode_char() {
    int unicode_id = BRAILLE_OFFSET;
    for (int i = 0; i < 8; i++) {
        if (block_map[i]) {
            unicode_id += TRANSFORMATION_MATRIX[i];
        }
    }
    return unicode_id;
}

void cell::reset() {
    std::fill(block_map, block_map + 8, 0);
}
