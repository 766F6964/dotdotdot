//
// Created by void on 5/29/20.
//

#include <algorithm>
#include "examples.h"
#include "../engine/geometry/triangle.h"
#include "../engine/geometry/line.h"


void examples::draw_triangle() {

    const int GRID_WIDTH = 80;  // 80 colums, which equals 2*80=160 pixels
    const int GRID_HEIGHT = 35; // 35 rows, which equals 4*35=140 pixels

    grid g(GRID_WIDTH, GRID_HEIGHT);

    auto triangle = triangle::get_triangle(20, 20, 140, 50, 80, 130);
    for (int i = 0; i < g.get_width(); i++) {
        for (int j = 0; j < g.get_height(); ++j) {
            if (std::find(triangle.begin(), triangle.end(), std::make_pair(i, j)) != triangle.end()) {
                g.set(i, j);
            }
        }
    }
    g.render();
}

void examples::draw_line() {
    const int GRID_WIDTH = 80;  // 80 colums, which equals 2*80=160 pixels
    const int GRID_HEIGHT = 35; // 35 rows, which equals 4*35=140 pixels

    grid g(GRID_WIDTH, GRID_HEIGHT);

    auto triangle  = line::get_line(20, 120, 120, 10);
    for (int i = 0; i < g.get_width(); i++) {
        for (int j = 0; j < g.get_height(); ++j) {
            if (std::find(triangle.begin(), triangle.end(), std::make_pair(i, j)) != triangle.end()) {
                g.set(i, j);
            }
        }
    }
    g.render();
}

