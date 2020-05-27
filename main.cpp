#include <iostream>
#include "engine/block.h"
#include "engine/utils.h"

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

    char chars[5];
    utils::int_to_uchar(b.to_unicode_char(), chars);
    std::cout << chars << std::endl;

    return 0;
}
