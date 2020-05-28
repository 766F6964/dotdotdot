#include <iostream>
#include <math.h>
#include "engine/block.h"
#include "engine/utils.h"
#include "engine/grid.h"

// References & Resources:
//
// http://www.alanwood.net/unicode/braille_patterns.html
// https://github.com/asciimoo/drawille/blob/master/drawille.py
// https://blog.jverkamp.com/2014/05/30/braille-unicode-pixelation/
// http://ioccc.org/2012/endoh1/hint.html
// https://github.com/null93/drawille

// https://stackoverflow.com/questions/23461499/decimal-to-unicode-char-in-c

int main() {
    block b;
    b.set(0, 0);
    b.set(1, 1);
    b.set(0, 2);
    b.set(1, 3);

    grid g(75, 6);

    std::cout << "Width: " << g.get_width() << std::endl;
    std::cout << "Height: " << g.get_height() << std::endl;

    for (int x = 0; x <= g.get_width() * 8; x++) {
        g.set(x / 10, (int) round(10 + cos(x * M_PI / 180) * 10));
    }
    g.render();

    //char chars[5];
    //utils::int_to_uchar(b.to_unicode_char(), chars);
    //std::cout << chars << std::endl;

    return 0;
}
