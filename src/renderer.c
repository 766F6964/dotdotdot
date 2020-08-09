// Explanation of rendering process:
//
// 1) Render is initialized with grid ptr
// 2) Renderer needs to copy that grid and store it as grid_cached
// 3) When renderer update is called, the grid passed as parameter is the current one
// 3.1) If grid_cached != null -> render difference
// 3.2) If grid_cached == null -> render grid normally and then set cached grid to the grid that was just rendered
// 4) After rendering increase frame rendered counter

#include "grid.h"
#include "unicode.h"
#include "renderer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "constants.h"

render_context* p_render_context;
const int braille_offset = 0x2800;
const int TRANSFORMATION_MATRIX[8] ={ 0x01, 0x02, 0x04, 0x40, 0x08, 0x10, 0x20, 0x80 };
wchar_t lookup_table[256] ={};


void renderer_new(grid *p_grid) {

    // Generate braille lookup table
    grid_generate_lookup_table();

    // Copy initial grid, to cache it
    grid *p_cached_grid = calloc(1, sizeof(*p_grid));
    memcpy(p_cached_grid, p_grid, sizeof(*p_cached_grid));

    // Store cached grid in render_context
    p_render_context = calloc(1, sizeof(*p_render_context));
    p_render_context->p_cached_grid = p_cached_grid;
    p_render_context->frames_rendered = 0;

}

void renderer_update(grid* p_grid)
{
    // ToDo: Only render the characters that changed from current grid to cached grid
    // ToDo: Get character coordinates from grid coordinates

    printf("Rendering frame %i\n", p_render_context->frames_rendered);

    for (int i = 0; i < p_grid->buffer_size; ++i)
    {
        char uc[5];
        int braille = lookup_table[p_grid->buffer[i]];
        int_to_unicode_char(braille, uc);

        if (i % (p_grid->width / group_width) == 0 && i != 0)
        {
            printf("\n");
        }
        printf(uc);
    }
    printf("\n");

    // ToDo: Update p_cached_grid
    p_render_context->frames_rendered++;
}

void renderer_free()
{
    free(p_render_context->p_cached_grid);
    free(p_render_context);
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