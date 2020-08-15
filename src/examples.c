#include "grid.h"
#include "renderer.h"

void example_filling_bar()
{
    grid *g = grid_new(100, 24);
    renderer_new(g);

    // Fill grid from left to right (simple animation)
    renderer_update(g);
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 24; j++)
        {
            grid_set_pixel(g, i, j);
        }
        renderer_update(g);
    }

    // Free allocations
    renderer_free();
}

void example_sine_tracking()
{
    grid *g = grid_new(100, 40);
    renderer_new(g);

    for (int x = 0; x < 100; x++)
    {
        for (int y = 0; y < 40; y++)
        {
            if (x % 2 == 0 && y % 2 == 0)
            {
                grid_set_pixel(g, x, y);
                renderer_update(g);
            }
        }
    }
    
    // Free allocations
    renderer_free();
    grid_free(g);
}