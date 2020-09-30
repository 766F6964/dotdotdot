#ifndef RENDERER_H
#define RENDERER_H

#include "grid.h"

typedef struct {
    grid* p_cached_grid;
    int frames_rendered;
} render_context;

void renderer_new(grid* p_grid);
void renderer_raw_dump(grid* p_grid);
void renderer_update(grid* p_grid);
void renderer_free();
void grid_generate_lookup_table();

#endif
