//
// Created by void on 5/27/20.
//

#ifndef DOTS_GRID_H
#define DOTS_GRID_H

#include <vector>
#include "cell.h"

class grid {
public:

    grid(int width, int height);

    int get_width() const;

    int get_height() const;

    void check_bounds(int x, int y) const;

    void set(int x, int y);

    void unset(int x, int y);

    void modify(int x, int y, bool value);

    void clear();

    void render();

private:

    int width;
    int height;

    std::vector<cell*> screen;

};


#endif //DOTS_GRID_H
