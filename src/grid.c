#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
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