//
// Created by void on 5/29/20.
//

#ifndef DOTS_POINT_H
#define DOTS_POINT_H


class point {
public:
    point(int x, int y);
    int get_x();
    int get_y();

private:
    int x_coord;
    int y_coord;
};


#endif //DOTS_POINT_H
