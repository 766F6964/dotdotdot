#include "grid.h"
#include "renderer.h"
#include <stdlib.h>

frame* p_render_info;


frame *renderer_new(grid *p_grid)
{
    p_render_info = calloc(1, sizeof(*p_render_info));

    p_render_info->grid = p_grid;
    p_render_info->frames_rendered = 0;

    return p_render_info;
}

frame* renderer_update(grid* p_grid)
{
    return NULL;
}

void renderer_free(frame *p_frame)
{
    // Maybe we should free if we need to reuse the grid buffer?
    free(p_render_info->grid);
    free(p_render_info);
}