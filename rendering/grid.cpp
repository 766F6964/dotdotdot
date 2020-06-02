//
// Created by void on 5/31/20.
//

#include <stdexcept>
#include <iostream>
#include "grid.h"

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
        int_to_unicode_char(braille, uc);

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

bool grid::is_set(int x, int y) {
    int bytes_per_line = grid_width / group_width;
    int byte_idx = (x / group_width) + (y / group_height) * bytes_per_line;
    int bit_idx = (x % group_width) * group_height + (y % group_height);

    return (buffer[byte_idx] & (1 << bit_idx)) != 0;
}


void grid::generate_lookup_table() {
    for (int i = 0; i < 256; ++i) {
        int unicode = BRAILLE_OFFSET;
        for (int j = 0; j < 8; ++j) {
            if (((i & (1 << j)) != 0))
                unicode += TRANSFORMATION_MATRIX[j];
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

// https://stackoverflow.com/questions/23461499/decimal-to-unicode-char-in-c
void grid::int_to_unicode_char(unsigned int code, char *chars) {
    if (code <= 0x7F) {
        chars[0] = (code & 0x7F);
        chars[1] = '\0';
    } else if (code <= 0x7FF) {
        // one continuation byte
        chars[1] = 0x80 | (code & 0x3F);
        code = (code >> 6);
        chars[0] = 0xC0 | (code & 0x1F);
        chars[2] = '\0';
    } else if (code <= 0xFFFF) {
        // two continuation bytes
        chars[2] = 0x80 | (code & 0x3F);
        code = (code >> 6);
        chars[1] = 0x80 | (code & 0x3F);
        code = (code >> 6);
        chars[0] = 0xE0 | (code & 0xF);
        chars[3] = '\0';
    } else if (code <= 0x10FFFF) {
        // three continuation bytes
        chars[3] = 0x80 | (code & 0x3F);
        code = (code >> 6);
        chars[2] = 0x80 | (code & 0x3F);
        code = (code >> 6);
        chars[1] = 0x80 | (code & 0x3F);
        code = (code >> 6);
        chars[0] = 0xF0 | (code & 0x7);
        chars[4] = '\0';
    } else {
        // unicode replacement character
        chars[2] = 0xEF;
        chars[1] = 0xBF;
        chars[0] = 0xBD;
        chars[3] = '\0';
    }
}
