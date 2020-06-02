//
// Created by void on 5/31/20.
//

#include <stdexcept>
#include <iostream>
#include "canvas.h"
#include "utils.h"

canvas::canvas(int width, int height) {
    this->grid_width = width;
    this->grid_height = height;

    if (width % 2 != 0)
        throw std::invalid_argument("Width must be a multiple of 2");
    if (height % 4 != 0)
        throw std::invalid_argument("Height must be a multiple of 4");

    generate_lookup_table();
    buffer.resize(this->grid_width / this->group_width * this->grid_height / this->group_height, 0);
}

void canvas::render() {
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

void canvas::set_pixel(int x, int y) {
    modify_pixel(x, y, 1);
}

void canvas::unset_pixel(int x, int y) {
    modify_pixel(x, y, 0);
}

void canvas::modify_pixel(int x, int y, int value) {
    validate_coordinates(x, y);
    int bytes_per_line = grid_width / group_width;
    int byte_idx = (x / group_width) + (y / group_height) * bytes_per_line;
    int bit_idx = (x % group_width) * group_height + (y % group_height);
    buffer[byte_idx] = (buffer[byte_idx] & ~(1 << bit_idx)) | (value << bit_idx);
}

bool canvas::get_pixel(int x, int y) {
    int bytes_per_line = grid_width / group_width;
    int byte_idx = (x / group_width) + (y / group_height) * bytes_per_line;
    int bit_idx = (x % group_width) * group_height + (y % group_height);

    return (buffer[byte_idx] & (1 << bit_idx)) != 0;
}


void canvas::generate_lookup_table() {
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

int canvas::get_buffer_size() {
    return this->buffer.size();
}

void canvas::clear() {
    for (int i = 0; i < get_buffer_size(); ++i) {
        buffer[i] = 0x00;
    }
}

void canvas::fill() {
    for (int i = 0; i < get_buffer_size(); ++i) {
        buffer[i] = 0xFF;
    }
}

void canvas::validate_coordinates(int x, int y) const {
    if (x >= grid_width || y >= grid_height || x < 0 || y < 0) {
        throw std::out_of_range("Coordinates do not describe a valid position in this grid");
    }
}

int canvas::get_width() {
    return grid_width;
}

int canvas::get_height() {
    return grid_height;
}


























/*
void canvas::check_bounds(int x, int y) const {
    if (x >= grid_width || y >= grid_height || x < 0 || y < 0) {
        throw std::out_of_range("Coordinates do not describe a valid position in the grid");
    }
}

using data_type = int; // change type to correctly group data not being integers
using group = std::vector<data_type>; // reprensents the values of one group
const data_type DEFAULT{-1};

*//**
@param data_begin begin iterator of the input data
@param data_end end iterator of the input data
@return a vector of all groups from top to bottom, from left to right.
*//*

template<class const_it>
std::vector<group>
grouping(int grid_width, int grid_height, int group_width, int group_height, const_it data_begin, const_it data_end) {
    const int GROUPS_PER_ROW{grid_width / group_width};
    const int GROUPS_PER_COL{grid_height / group_height};
    const int NUMBER_GROUPS{GROUPS_PER_ROW * GROUPS_PER_COL};
    const int GROUP_SIZE{group_width * group_height};

    std::vector<group> result(NUMBER_GROUPS,
                              group(GROUP_SIZE, DEFAULT)); // create empty result vector with correct size.
    std::size_t group_index{0}; // id of the current group
    std::size_t group_position_y{0}; // currrent vertical position inside a group block
    std::size_t group_position_x{0}; // current horizontal position inside a group block
    std::size_t row{0}; // current row with respect to the groups
    std::size_t col{0}; // current column with respect to the groups

    // iterate through all input data, copy data cell to target structur (result), calculate the correct indices for the next input data cell
    for (const_it it{data_begin}; it != data_end; ++it) {
        result[group_index][group_position_y + group_height * group_position_x] = *it;

        group_position_x = (group_position_x + 1) % group_width; // new horizontal position inside group
        auto old_col{col};
        col = (col + (group_position_x == 0)) % GROUPS_PER_ROW; // new column with respect to the groups
        auto old_group_position_y{group_position_y};
        group_position_y =
                (group_position_y + (col == 0 && col != old_col)) % group_height; // new vertical position inside group
        row = (row + (group_position_y == 0 && group_position_y != old_group_position_y)) %
              GROUPS_PER_COL; // new row with respect to the groups
        group_index = col + GROUPS_PER_ROW * row;
    }
    return result;
}*/
/*

void canvas::render() {
    //for (int i = 0; i < this->grid_width * this->grid_height; i++) {
    //    std::cout << this->screen[i] << "  (" << i << ")\n";
    // }

    std::cout << "Grid Width:" << grid_width << std::endl;
    std::cout << "Grid Height:" << grid_height << std::endl;

    auto res = grouping(grid_width, grid_height, group_width, group_height, screen.begin(), screen.end());

    for (int i = 0; i < res.size(); ++i) {

        for (int j = 0; j < res[i].size(); ++j) {

            std::cout << res[i][j] << std::endl;
        }
        std::cout << "---" << std::endl;
    }
}

void canvas::clear_pixel(int x, int y) {
    check_bounds(x, y);
    screen[y * grid_width + x] = false;
}

int canvas::get_height() const {
    return grid_height;
}

int canvas::get_width() const {
    return grid_width;
}

void canvas::draw_line(int x1, int y1, int x2, int y2) {

}

void canvas::clear() {
    std::fill(screen.begin(), screen.end(), false);
}

void canvas::fill() {
    std::fill(screen.begin(), screen.end(), true);
}

void canvas::draw_pixel(int x, int y, int val) {
    check_bounds(x, y);
    screen[y * grid_width + x] = val;
}

*/
