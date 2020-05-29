#include <algorithm>
#include "engine/grid.h"
#include "engine/geometry/line.h"
#include "engine/geometry/triangle.h"

// References & Resources:
//
// http://www.alanwood.net/unicode/braille_patterns.html
// https://github.com/asciimoo/drawille/blob/master/drawille.py
// https://blog.jverkamp.com/2014/05/30/braille-unicode-pixelation/
// http://ioccc.org/2012/endoh1/hint.html
// https://github.com/null93/drawille

int main() {

    const int GRID_WIDTH = 80;
    const int GRID_HEIGHT = 35;

    grid g(GRID_WIDTH, GRID_HEIGHT);

    auto triangle = triangle::get_triangle(20, 5, 140, 60, 80, 100);

    for (int i = 0; i < g.get_width(); i++) {
        for (int j = 0; j < g.get_height(); ++j) {
            if (std::find(triangle.begin(), triangle.end(), std::make_pair(i, j)) != triangle.end()) {
                g.set(i, j);
            }
        }
    }
    g.render();
    return 0;
}
