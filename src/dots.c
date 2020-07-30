#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

const int group_height = 2;
const int group_width = 4;
const int braille_offset = 0x2800;
const int TRANSFORMATION_MATRIX[8] = {0x01, 0x02, 0x04, 0x40, 0x08, 0x10, 0x20, 0x80};
wchar_t lookup_table[256] = {};

typedef struct
{
    int width;
    int height;
    int *buffer;
} grid;

// Prototypes
grid *grid_new(int grid_width, int grid_height);
void grid_free(grid *p_grid);

void grid_clear(grid *g);
void grid_fill(grid *g);
void grid_render(grid *g);
void grid_modify_pixel(grid *g, int x, int y, int value);
void grid_set_pixel(grid *g, int x, int y);
void grid_unset_pixel(grid *g, int x, int y);

void grid_generate_lookup_table();
void int_to_unicode_char(unsigned int code, char *chars);


// Implementations
grid *grid_new(int grid_width, int grid_height)
{
    if ((grid_width % 2 != 0) || (grid_height % 4 != 0))
        return NULL;

    grid_generate_lookup_table();

    grid *p_grid = calloc(1, sizeof(*p_grid));

    p_grid->width = grid_width;
    p_grid->height = grid_height;

    p_grid->buffer = calloc(grid_width / group_width * grid_height / group_height, sizeof(int));
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



void int_to_unicode_char(unsigned int code, char *chars)
{
    if (code <= 0x7F)
    {
        chars[0] = (code & 0x7F);
        chars[1] = '\0';
    }
    else if (code <= 0x7FF)
    {
        // one continuation byte
        chars[1] = 0x80 | (code & 0x3F);
        code = (code >> 6);
        chars[0] = 0xC0 | (code & 0x1F);
        chars[2] = '\0';
    }
    else if (code <= 0xFFFF)
    {
        // two continuation bytes
        chars[2] = 0x80 | (code & 0x3F);
        code = (code >> 6);
        chars[1] = 0x80 | (code & 0x3F); 
        code = (code >> 6);
        chars[0] = 0xE0 | (code & 0xF);
        chars[3] = '\0';
    }
    else if (code <= 0x10FFFF)
    {
        // three continuation bytes
        chars[3] = 0x80 | (code & 0x3F);
        code = (code >> 6);
        chars[2] = 0x80 | (code & 0x3F);
        code = (code >> 6);
        chars[1] = 0x80 | (code & 0x3F);
        code = (code >> 6);
        chars[0] = 0xF0 | (code & 0x7);
        chars[4] = '\0';
    }
    else
    {
        // unicode replacement character
        chars[2] = 0xEF;
        chars[1] = 0xBF;
        chars[0] = 0xBD;
        chars[3] = '\0';
    }
}

void grid_clear(grid *g)
{
    for (int i = 0; i < g->width * g->height; ++i)
    {
        g->buffer[i] = 0x00;
    }
}

void grid_fill(grid *g)
{
    for (int i = 0; i < g->width * g->height; ++i)
    {
        g->buffer[i] = 0xFF;
    }
}


void grid_render(grid *g)
{

    for (int i = 0; i < (g->width * g->height); ++i)
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

int main()
{

    printf("Creating grid.\n");

    grid *g = grid_new(12, 12);
    grid_clear(g);
    
    grid_set_pixel(g, 0,0);
    grid_set_pixel(g, 1,1);
    grid_set_pixel(g, 2,2);
    grid_set_pixel(g, 3,3);
    grid_set_pixel(g, 4,4);
    grid_set_pixel(g, 5,5);
    grid_set_pixel(g, 6,6);
    grid_set_pixel(g, 7,7);
    grid_set_pixel(g, 8,8);
    grid_set_pixel(g, 9,9);
    grid_set_pixel(g, 10,10);
    grid_set_pixel(g, 11,11);

    // Print buffer content
    for (int i = 0; i < g->width * g->height; i++)
    {
        printf("#%i -> %i\n", i, *&g->buffer[i]);
    }

    grid_render(g);
    grid_free(g);

    return 0;
}