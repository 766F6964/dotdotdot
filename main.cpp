#include "rendering/canvas.h"

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

    int width = 120;
    int height = 80;
    canvas c(120, 80); // 6 chars in je 2 lines

    // Create border
    for (int i = 0; i < width; ++i) {
        c.set_pixel(i, 0);
        c.set_pixel(i, height - 1);
    }
    for (int i = 0; i < height; ++i) {
        c.set_pixel(0, i);
        c.set_pixel(width - 1, i);
    }

    c.render();
    c.clear();
    c.render();
    c.fill();
    c.render();

    return 0;
}
