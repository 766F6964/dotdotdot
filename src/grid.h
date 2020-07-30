#ifndef GRID_H
#define GRID_H

typedef struct
{
    int width;
    int height;
    int buffer_size;
    int *buffer;
} grid;

grid *grid_new(int grid_width, int grid_height);
void grid_free(grid *p_grid);
void grid_generate_lookup_table();
void grid_clear(grid *g);
void grid_fill(grid *g);
void grid_render(grid *g);
void grid_modify_pixel(grid *g, int x, int y, int value);
void grid_set_pixel(grid *g, int x, int y);
void grid_unset_pixel(grid *g, int x, int y);
void grid_draw_line(grid *g, int x1, int y1, int x2, int y2);
void grid_draw_triangle(grid *g, int x1, int y1, int x2, int y2, int x3, int y3);

#endif