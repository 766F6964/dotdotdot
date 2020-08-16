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
    int width = 120;
    int height = 40;

    grid *g = grid_new(width, height);
    renderer_new(g);




    // Draw curve
    int i = 0;
    double c = 0;
    double a = 19;
    double b = 0.05;

    double d = 19;
    while (1)
    {
        
        grid_clear(g);
        
        // Draw line
        int pos_x = width - 1;
        int pos_y = (height + sin(i * 0.03) * height) / 2;
        grid_draw_line(g, 0, height / 2, pos_x, pos_y);


        c += 0.03;

        for (int j = 0; j < width; j++)
        {

            int y = (int)calc_sine_curve(a, b, c, d, j);
            //int curve_coord = (height + sin(j * 0.05) * height) / 2;

            grid_set_pixel(g, j, y);
        } 
        renderer_update(g);
        i++;
    }
    /*
    int i = 0;
    while (1)
    {

        grid_clear(g);

        // Draw line
        //int pos_x = width - 1;
        //int pos_y = calc_sine(height, i);
        //grid_draw_line(g, 0, height / 2, pos_x, pos_y);

        // Draw curve
        for (int j = 0; j < width; j++)
        {   

            int curve_coord = (height + sin(j * 0.05) * height) / 2;
            grid_set_pixel(g, j, curve_coord);
        }

        renderer_update(g);

        i++;
    }
    */

    // Free allocations
    renderer_free();
    grid_free(g);
}