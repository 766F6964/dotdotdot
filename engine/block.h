//
// Created by void on 5/27/20.
//

#ifndef DOTS_BLOCK_H
#define DOTS_BLOCK_H


class block {
public:

    block();

    void check_bounds(int x, int y);

    void set(int x, int y);

    void unset(int x, int y);

    bool is_set(int x, int y);

    void modify(int x, int y, bool value);

    void reset();

    int to_unicode_char();

private:


    const int BRAILLE_OFFSET = 0x2800;
    const int TRANSFORMATION_MATRIX[8] = {0x01, 0x08, 0x02, 0x10, 0x04, 0x20, 0x40, 0x80};
    bool block_map[8];

};


#endif //DOTS_BLOCK_H
