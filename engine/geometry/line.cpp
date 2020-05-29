//
// Created by void on 5/29/20.
//

#include "line.h"

std::vector<std::pair<int, int>> line::get_line(int x1, int y1, int x2, int y2) {

    int x_diff = std::max(x1, x2) - std::min(x1, x2);
    int y_diff = std::max(y1, y2) - std::min(y1, y2);
    int x_direction = x1 <= x2 ? 1 : -1;
    int y_direction = y1 <= y2 ? 1 : -1;

    int r = std::max(x_diff, y_diff);
    std::vector<std::pair<int, int>> coords;

    for (int i = 0; i < r; i++) {
        int x = x1;
        int y = y1;

        if (y_diff)
            y += (float(i) * y_diff) / r * y_direction;
        if (x_diff)
            x += (float(i) * x_diff) / r * x_direction;

        coords.emplace_back(x, y);
    }
    return coords;
}
