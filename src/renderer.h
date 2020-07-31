#ifndef RENDERER_H
#define RENDERER_H

#include "grid.h"

typedef struct {
    // Maybe include something to measure frame pacing?
    grid* grid;
    int frames_rendered;
} frame;

frame* renderer_new(grid* p_grid);
frame* renderer_update(grid* p_grid); // Maybe grid* instead?
void renderer_free();

#endif
