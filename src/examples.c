#include <math.h>
#include "grid.h"
#include "renderer.h"
#include <stdio.h>

void example_filling_bar()
{
    int width = 100;
    int height = 24;

    grid *g = grid_new(width, height);
    renderer_new(g);

    // Fill grid from left to right (simple animation)
    renderer_update(g);
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            grid_set_pixel(g, i, j);
        }
        renderer_update(g);
    }

    // Free allocations
    renderer_free();
    grid_free(g);
}

void example_build_block()
{
    int width = 100;
    int height = 40;

    grid *g = grid_new(width, height);
    renderer_new(g);

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            grid_set_pixel(g, x, y);
            renderer_update(g);
        }
    }

    // Free allocations
    renderer_free();
    grid_free(g);
}

//#define degToRad(angleInDegrees) ((angleInDegrees)*M_PI / 180.0)

double calc_sine(int height, double x)
{
    return height + sin((x + 1) * M_PI / 180.0f) * height;
}

void example_sine_tracking()
{
    int width = 120;
    int height = 40;

    grid *g = grid_new(width, height);
    renderer_new(g);

    int i = 0;
    while (1)
    {

        grid_clear(g);

        // Draw line
        int pos_x = width - 1;
        int pos_y = (height + sin(i * 0.05) * height) / 2;
        grid_draw_line(g, 0, height / 2, pos_x, pos_y);

        // Draw curve
        for (int j = 0; j < width; j++)
        {
            int curve_coord = (height + sin(j * 0.05) * height) / 2;
            grid_set_pixel(g, j, curve_coord);
        }

        renderer_update(g);

        i++;
    }

    // Free allocations
    renderer_free();
    grid_free(g);
}