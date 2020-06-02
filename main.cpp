#include "examples/examples.h"
#include "rendering/canvas.h"
#include "rendering/utils.h"
#include <iostream>
#include <algorithm>


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

    /*
        +----+----+
        | 1  | 0  |
        +----+----+
        | 0  | 1  |
        +----+----+
        | 1  | 0  |
        +----+----+
        | 0  | 1  |
        +----+----+
     */


    /* Order:
    +----+----+
    | a  | d  |
    +----+----+
    | b  | e  |
    +----+----+
    | c  | f  |
    +----+----+
    | g  | h  |
    +----+----+
    */


    // Try to generate a lookup table for every possible braille config

    for (int i = 0; i < 256; ++i) {
        // Read all 8 bits

        // Create bit representation of braille grid
        bool block_map[8];

        std::cout << "Original ";
        for (int j = 0; j < 8; ++j) {
            std::cout << ((i & (1 << j)) != 0);
            block_map[j] = ((i & (1 << j)) != 0);
        }

        std::reverse(std::begin(block_map), std::end(block_map));

        std::cout << std::endl;
        std::cout << "Transformed ";
        int unicode = i;

        // Apply matrix transformation
        if (block_map[0] == 1)
            unicode += 0x01;
        if (block_map[1] == 1)
            unicode += 0x02;
        if (block_map[2] == 1)
            unicode += 0x04;
        if (block_map[3] == 1)
            unicode += 0x08;
        if (block_map[4] == 1)
            unicode += 0x10;
        if (block_map[5] == 1)
            unicode += 0x20;
        if (block_map[6] == 1)
            unicode += 0x40;
        if (block_map[7] == 1)
            unicode += 0x80;

        std::cout << "Braille Index #" << unicode << std::endl;
        std::cout << "Braille Offset: " << 0x2800 + unicode << std::endl;
        std::cout << "Iteration: " << i << std::endl;

        char uc[5];
        utils::int_to_uchar(0x2800 + unicode, uc);
        std::cout << "Braille Character: " << uc << std::endl;


        std::cout << std::endl;
    }


    /*int number = 19;
    canvas can(2, 4);

    can.set_pixel(0, 0);
    can.set_pixel(0, 1);
    can.set_pixel(1, 1);

    // Grab positions



    bool a = can.get_pixel(0, 0);
    bool b = can.get_pixel(0, 1);
    bool c = can.get_pixel(0, 2);
    bool d = can.get_pixel(1, 0);
    bool e = can.get_pixel(1, 1);
    bool f = can.get_pixel(1, 2);
    bool g = can.get_pixel(0, 3);
    bool h = can.get_pixel(1, 3);

    int unicode = 0;

    if (a == true)
        unicode += 0x01;
    if (b == true)
        unicode += 0x02;
    if (c == true)
        unicode += 0x04;
    if (d == true)
        unicode += 0x08;
    if (e == true)
        unicode += 0x10;
    if (f == true)
        unicode += 0x20;
    if (g == true)
        unicode += 0x40;
    if (h == true)
        unicode += 0x80;

    std::cout << "Braille Char #" << unicode << std::endl;
    std::cout << "Braille Offset: 0x" << std::hex << 0x2800 + unicode << std::endl;

    char uc[5];
    utils::int_to_uchar(0x2800 + unicode, uc);
    std::cout << uc << std::endl;*/


    /*  c.set_pixel(0, 0);
      // c.set_pixel(0, 1);
      //c.set_pixel(1, 0);
      c.set_pixel(1, 1);
      c.set_pixel(0, 2);
      // c.set_pixel(1, 2);
      c.set_pixel(0, 3);
      // c.set_pixel(1, 3);
  */
    //can.render();

    return 0;
}
