//
// Created by void on 5/29/20.
//

#include "triangle.h"
#include "line.h"

std::vector<std::pair<int, int>> triangle::get_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    std::vector<std::pair<int, int>> coords;

    auto line1 = line::get_line(x1, y1, x2, y2);
    auto line2 = line::get_line(x2, y2, x3, y3);
    auto line3 = line::get_line(x3, y3, x1, y1);

    for (auto & i : line1) {
        coords.emplace_back(i.first, i.second);
    }
    for (auto & i : line2) {
        coords.emplace_back(i.first, i.second);
    }
    for (auto & i : line3) {
        coords.emplace_back(i.first, i.second);
    }
    return coords;
}
