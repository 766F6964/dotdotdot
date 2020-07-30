#include "grid.h"

int main()
{
    grid *g = grid_new(12, 12);
    grid_clear(g);
    
    grid_draw_line(g, 11, 0, 0, 11);
    grid_draw_line(g, 0, 0, 11, 11);

    grid_render(g);

    return 0;
}