#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include "grid.h"
#include "unicode.h"

// Variables
const int group_height = 4;
const int group_width = 2;
const int braille_offset = 0x2800;
const int TRANSFORMATION_MATRIX[8] = {0x01, 0x02, 0x04, 0x40, 0x08, 0x10, 0x20, 0x80};
wchar_t lookup_table[256] = {};

grid *grid_new(int grid_width, int grid_height)
{
    if ((grid_width % 2 != 0) || (grid_height % 4 != 0))
        return NULL;

    grid_generate_lookup_table();

    grid *p_grid = calloc(1, sizeof(*p_grid));

    p_grid->width = grid_width;
    p_grid->height = grid_height;
    p_grid->buffer_size = grid_width / group_width * grid_height / group_height;
    p_grid->buffer = calloc(p_grid->buffer_size, sizeof(int));

    return p_grid;
}

void grid_free(grid *p_grid)
{
    free(p_grid->buffer);
    free(p_grid);
}

void grid_generate_lookup_table()
{
    for (int i = 0; i < 256; ++i)
    {
        int unicode = braille_offset;
        for (int j = 0; j < 8; ++j)
        {
            if (((i & (1 << j)) != 0))
            {
                unicode += TRANSFORMATION_MATRIX[j];
            }
        }
        lookup_table[i] = unicode;
    }
}

void grid_clear(grid *g)
{
    for (int i = 0; i < g->buffer_size; ++i)
    {
        g->buffer[i] = 0x00;
    }
}

void grid_fill(grid *g)
{
    for (int i = 0; i < g->buffer_size; ++i)
    {
        g->buffer[i] = 0xFF;
    }
}

void grid_render(grid *g)
{
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
}

void grid_render_loop(grid *g)
{
    int fps_cap = 30;
    
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    grid_render(g);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    unsigned long delta = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
 
    printf("Rendertime: %dµs\n", delta);
}

void grid_modify_pixel(grid *g, int x, int y, int value)
{
    // ToDo validate coords
    int bytes_per_line = g->width / group_width;
    int byte_idx = (x / group_width) + (y / group_height) * bytes_per_line;
    int bit_idx = (x % group_width) * group_height + (y % group_height);
    g->buffer[byte_idx] = (g->buffer[byte_idx] & ~(1 << bit_idx)) | (value << bit_idx);
}

void grid_set_pixel(grid *g, int x, int y)
{
    grid_modify_pixel(g, x, y, 1);
}

void grid_unset_pixel(grid *g, int x, int y)
{
    grid_modify_pixel(g, x, y, 0);
}

void grid_draw_line(grid *g, int x1, int y1, int x2, int y2)
{
    // Bresenham's line algorithm
    int x_diff = x1 > x2 ? x1 - x2 : x2 - x1;
    int y_diff = y1 > y2 ? y1 - y2 : y2 - y1;
    int x_direction = x1 <= x2 ? 1 : -1;
    int y_direction = y1 <= y2 ? 1 : -1;

    int err = (x_diff > y_diff ? x_diff : -y_diff) / 2;
    int err2;

    while (1)
    {
        grid_set_pixel(g, x1, y1);
        if (x1 == x2 && y1 == y2)
        {
            break;
        }
        int err2 = err;
        if (err2 > -x_diff)
        {
            err -= y_diff;
            x1 += x_direction;
        }
        if (err2 < y_diff)
        {
            err += x_diff;
            y1 += y_direction;
        }
    }
}

void grid_draw_triangle(grid *g, int x1, int y1, int x2, int y2, int x3, int y3)
{
    // ToDo: Add filling algorithm
    grid_draw_line(g, x1, y1, x2, y2);
    grid_draw_line(g, x2, y2, x3, y3);
    grid_draw_line(g, x3, y3, x1, y1);
}