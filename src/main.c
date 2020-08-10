#include <stdio.h>
#include "grid.h"
#include "renderer.h"

int main()
{
    // Create initial grid
    grid* g = grid_new(12, 12);
    renderer_new(g);
    
    // Fill grid from left to right (simple animation)
    renderer_update(g);  
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            grid_set_pixel(g, i, j);
        }
        renderer_update(g);      
    }

    // Free allocations
    renderer_free();
    return 0;
}