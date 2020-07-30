#include "grid.h"

int main()
{
    grid *g = grid_new(12, 12);
    grid_clear(g);
    
    grid_set_pixel(g, 0,0);
    grid_set_pixel(g, 1,1);
    grid_set_pixel(g, 2,2);
    grid_set_pixel(g, 3,3);
    grid_set_pixel(g, 4,4);
    grid_set_pixel(g, 5,5);
    grid_set_pixel(g, 6,6);
    grid_set_pixel(g, 7,7);
    grid_set_pixel(g, 8,8);
    grid_set_pixel(g, 9,9);
    grid_set_pixel(g, 10,10);
    grid_set_pixel(g, 11,11);
    grid_render(g);

    grid_fill(g);
    grid_render(g);

    grid_clear(g);
    grid_render(g);
    
    grid_free(g);

    return 0;
}