//#include "grid.h"
#include "renderer.h"
#include <stdlib.h>

frame* p_render_info;


frame* renderer_new(grid *p_grid)
{

    p_render_info = calloc(1, sizeof(*p_render_info));

    p_render_info->grid = p_grid;
    p_render_info->frames_rendered = 0;

    return p_render_info;
}

frame* renderer_update(grid* p_grid)
{
    // Compare new grid and previous grid and update accordingly
    // Only re-render the changes from old to new grid

    //grid* p_grid_old = p_render_info->grid;



    // ToDo: Calculate cursor position for printed characters that need to be updated

    /*
    for (int i = 0; i < g->buffer_size; ++i)
    {
        char uc[5];
        int braille = lookup_table[g->buffer[i]];
        int_to_unicode_char(braille, uc);

        if (i % (g->width / group_width) == 0 && i != 0)
        {
            printf("\n");
        }
        printf(uc);
    }
    printf("\n");
    */
    return NULL; // ToDo: Return actual frame
}

void renderer_free(frame *p_frame)
{
    // Maybe we should free if we need to reuse the grid buffer?
    free(p_render_info->grid);
    free(p_render_info);
}