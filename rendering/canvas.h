//
// Created by void on 5/31/20.
//

#ifndef DOTS_CANVAS_H
#define DOTS_CANVAS_H


#include <vector>

class canvas {
public:

    canvas(int width, int height);

    void clear();

    void fill();

    void set_pixel(int x, int y);

    void unset_pixel(int x, int y);

    bool get_pixel(int x, int y);

    int get_width();
    int get_height();

    int get_buffer_size();

    void render();

private:

    void validate_coordinates(int x, int y) const;

    void modify_pixel(int x, int y, int value);

    void transform(int value, int byte_index);

    void generate_lookup_table();


    const int BRAILLE_OFFSET = 0x2800;
    const int TRANSFORMATION_MATRIX[8] = {0x01, 0x08, 0x02, 0x10, 0x04, 0x20, 0x40, 0x80};

    wchar_t lookup_table[256]{};

    int grid_width;
    int grid_height;

    const int group_width = 2;
    const int group_height = 4;

   std::vector<int> buffer;

};


#endif //DOTS_CANVAS_H
