//
// Created by void on 5/27/20.
//

#include "utils.h"

// https://stackoverflow.com/questions/23461499/decimal-to-unicode-char-in-c
void utils::int_to_uchar(unsigned int code, char *chars) {
    if (code <= 0x7F) {
        chars[0] = (code & 0x7F);
        chars[1] = '\0';
    } else if (code <= 0x7FF) {
        // one continuation byte
        chars[1] = 0x80 | (code & 0x3F);
        code = (code >> 6);
        chars[0] = 0xC0 | (code & 0x1F);
        chars[2] = '\0';
    } else if (code <= 0xFFFF) {
        // two continuation bytes
        chars[2] = 0x80 | (code & 0x3F);
        code = (code >> 6);
        chars[1] = 0x80 | (code & 0x3F);
        code = (code >> 6);
        chars[0] = 0xE0 | (code & 0xF);
        chars[3] = '\0';
    } else if (code <= 0x10FFFF) {
        // three continuation bytes
        chars[3] = 0x80 | (code & 0x3F);
        code = (code >> 6);
        chars[2] = 0x80 | (code & 0x3F);
        code = (code >> 6);
        chars[1] = 0x80 | (code & 0x3F);
        code = (code >> 6);
        chars[0] = 0xF0 | (code & 0x7);
        chars[4] = '\0';
    } else {
        // unicode replacement character
        chars[2] = 0xEF;
        chars[1] = 0xBF;
        chars[0] = 0xBD;
        chars[3] = '\0';
    }
}
