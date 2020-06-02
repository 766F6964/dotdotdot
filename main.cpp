#include "rendering/grid.h"
#include "geometry/line.h"

// References & Resources:
//
// http://www.alanwood.net/unicode/braille_patterns.html
// https://github.com/asciimoo/drawille/blob/master/drawille.py
// https://blog.jverkamp.com/2014/05/30/braille-unicode-pixelation/
// http://ioccc.org/2012/endoh1/hint.html
// https://github.com/null93/drawille
// https://www.cs.cornell.edu/~bindel/class/cs5220-f11/code/sph.pdf
// https://en.wikipedia.org/wiki/Braille_Patterns



int main() {

    const int GRID_WIDTH = 120;
    const int GRID_HEIGHT = 80;

    grid gr(GRID_WIDTH, GRID_HEIGHT);

    // Create border
    for (int i = 0; i < GRID_WIDTH; ++i) {
        gr.set_pixel(i, 0);
        gr.set_pixel(i, GRID_HEIGHT - 1);
    }
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        gr.set_pixel(0, i);
        gr.set_pixel(GRID_WIDTH - 1, i);
    }

    // Draw lines
    for (auto &line_dot : line::get_line(0, 0, GRID_WIDTH, GRID_HEIGHT)) {
        gr.set_pixel(line_dot.first, line_dot.second);
    }
    for (auto &line_dot : line::get_line(0, GRID_HEIGHT - 1, GRID_WIDTH - 1, 0)) {
        gr.set_pixel(line_dot.first, line_dot.second);
    }
    // Render output
    gr.render();

    return 0;
}
