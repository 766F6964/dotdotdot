#include <math.h>
#include "../src/grid.h"
#include "../src/renderer.h"
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
            grid_set_pixel(g, j, (height / 2 * sin(0.05 * j + shift) + height / 2));
        }

        // Move curve
        shift += 0.05;

        renderer_update(g);
    }

    // Free allocations
    renderer_free();
    grid_free(g);
}

void example_spiral_effect()
{
    int width = 60;
    int height = 32;

    grid *g = grid_new(width, height);
    renderer_new(g);

    // Start with an empty grid
    grid_clear(g);

    int m = width, n = height;
    int sr = 0, sc = 0, er = m - 1, ec = n - 1;
    while (sr <= er && sc <= ec)
    {
        for (int i = sc; i <= ec; ++i)
        {
            grid_set_pixel(g, sr, i);
            renderer_update(g);
        }
        for (int i = sr + 1; i <= er; ++i)
        {
            grid_set_pixel(g, i, ec);
            renderer_update(g);
        }
        for (int i = ec - 1; sr != er && i >= sc; --i)
        {
            grid_set_pixel(g, er, i);
            renderer_update(g);
        }
        for (int i = er - 1; sc != ec && i > sr; --i)
        {
            grid_set_pixel(g, i, sc);
            renderer_update(g);
        }
        sr++, sc++;
        er--, ec--;
    }

    // Free allocations
    renderer_free();
    grid_free(g);
}

void example_draw_border()
{
    int width = 100;
    int height = 40;
    int border_thickness = 5;

    grid *g = grid_new(width, height);
    renderer_new(g);

    // Draw border around the grid
    grid_draw_border(g, border_thickness);
    renderer_update(g);

    // Free allocations
    renderer_free();
    grid_free(g);
}