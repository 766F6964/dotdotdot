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

// a = stretch y
// b = stretch x
// c = move x
// d = move y
double calc_sine_curve(double a, double b, double c, double d, double x)
{
    return a * sin(b * x + c) + d;
}

void example_sine_tracking()
{
    int width = 124;
    int height = 40;

    grid *g = grid_new(width, height);
    renderer_new(g);

    double shift = 0;

    while (1)
    {
        grid_clear(g);

        // Draw line
        grid_draw_line(g, 0, height / 2, width - 1, (height + sin(shift) * height) / 2);

        // Draw curve
        for (int j = 0; j < width; j++)
        {
            grid_set_pixel(g, j, (int)calc_sine_curve(height / 2, 0.05, shift, height / 2, j));
        }

        // Move curve
        shift += 0.05;

        renderer_update(g);
    }

    // Free allocations
    renderer_free();
    grid_free(g);
}