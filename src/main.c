#include <stdio.h>
#include "grid.h"
#include "renderer.h"

int main()
{
    grid *g = grid_new(24, 24);
    //frame *f = renderer_new(g);

    // Maybe something like renderer_set_opts() ?
    
    int cnt = 0;
    while (cnt)
    {

        // Modify grid
        grid_set_pixel(g, cnt % 23, cnt % 23);
        // Update renderer (Only re-render changes)
        //f = renderer_update(g);
        printf("Position (%i, %i)", cnt, cnt);
        // Print rendering info
        //printf("Rendered frame %i", f->frames_rendered);

        cnt++;
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