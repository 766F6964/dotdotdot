#include "grid.h"
#include "renderer.h"

int main()
{
    grid *g = grid_new(24, 24);
    frame *f = renderer_new(g);

    // Maybe something like renderer_set_opts() ?

    
    while (1) {

        // Modify grid

        f = renderer_update(g);
    }
    
    /*
    grid_clear(g);
    
    
    grid_draw_line(g, 23, 0, 0, 23);
    grid_draw_line(g, 0, 0, 23, 23);

    grid_render_loop(g);
    grid_clear(g);
    

    grid_draw_triangle(g, 2, 2, 23, 12, 10, 23);
    grid_render_loop(g);
    */
   
    return 0;
}