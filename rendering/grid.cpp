//
// Created by void on 5/31/20.
//

#include <stdexcept>
#include <iostream>
#include "grid.h"
#include "utils.h"

grid::grid(int width, int height) {
    this->grid_width = width;
    this->grid_height = height;

    if (width % 2 != 0)
        throw std::invalid_argument("Width must be a multiple of 2");
    if (height % 4 != 0)
        throw std::invalid_argument("Height must be a multiple of 4");

    generate_lookup_table();
    buffer.resize(this->grid_width / this->group_width * this->grid_height / this->group_height, 0);
}

void grid::render() {
    for (int i = 0; i < get_buffer_size(); ++i) {
        char uc[5];
        int braille = lookup_table[buffer[i]];
        utils::int_to_uchar(braille, uc);

        if (i % (grid_width / group_width) == 0 && i != 0) {
            std::cout << std::endl;
        }
        std::cout << uc;
    }
    std::cout << std::endl;
}

void grid::set_pixel(int x, int y) {
    modify_pixel(x, y, 1);
}

void grid::unset_pixel(int x, int y) {
    modify_pixel(x, y, 0);
}

void grid::modify_pixel(int x, int y, int value) {
    validate_coordinates(x, y);
    int bytes_per_line = grid_width / group_width;
    int byte_idx = (x / group_width) + (y / group_height) * bytes_per_line;
    int bit_idx = (x % group_width) * group_height + (y % group_height);
    buffer[byte_idx] = (buffer[byte_idx] & ~(1 << bit_idx)) | (value << bit_idx);
}

bool grid::get_pixel(int x, int y) {
    int bytes_per_line = grid_width / group_width;
    int byte_idx = (x / group_width) + (y / group_height) * bytes_per_line;
    int bit_idx = (x % group_width) * group_height + (y % group_height);

    return (buffer[byte_idx] & (1 << bit_idx)) != 0;
}


void grid::generate_lookup_table() {
    int transformation_matrix[8] = {0x01, 0x02, 0x04, 0x40, 0x08, 0x10, 0x20, 0x80};

    for (int i = 0; i < 256; ++i) {
        int unicode = 0x2800;
        for (int j = 0; j < 8; ++j) {
            if (((i & (1 << j)) != 0))
                unicode += transformation_matrix[j];
        }
        this->lookup_table[i] = unicode;
    }
}

int grid::get_buffer_size() {
    return this->buffer.size();
}

void grid::clear() {
    for (int i = 0; i < get_buffer_size(); ++i) {
        buffer[i] = 0x00;
    }
}

void grid::fill() {
    for (int i = 0; i < get_buffer_size(); ++i) {
        buffer[i] = 0xFF;
    }
}

void grid::validate_coordinates(int x, int y) const {
    if (x >= grid_width || y >= grid_height || x < 0 || y < 0) {
        throw std::out_of_range("Coordinates do not describe a valid position in this grid");
    }
}

int grid::get_width() const {
    return grid_width;
}

int grid::get_height() const {
    return grid_height;
}
