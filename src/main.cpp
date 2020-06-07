#include <iostream>
#include "rendering/grid.h"
#include "rendering/geometry/line.h"
#include "rendering/geometry/triangle.h"
#include "simulations/fluid/vec2d.h"

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
    grid g(50, 20);
    auto points = line::get_line(0, 0, 40, 20);

    for (auto &point : points) {
        g.set_pixel(point.first, point.second);
    }
    g.render();
    return 0;
}
