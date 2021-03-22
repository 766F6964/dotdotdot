#include "grid.h"
#include "unicode.h"
#include "renderer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include <ncurses.h>
#include <unistd.h>
#include <locale.h>

render_context* p_render_context;
const int braille_offset = 0x2800;
const int TRANSFORMATION_MATRIX[8] ={ 0x01, 0x02, 0x04, 0x40, 0x08, 0x10, 0x20, 0x80 };
wchar_t lookup_table[256] ={};


void renderer_new(grid *p_grid) {

    // Set locale for ncurses to process unicode correctly
    setlocale(LC_ALL, "");

    // Generate braille lookup table
    grid_generate_lookup_table();

    // Create copy of initial grid for caching, but zero out buffer
    grid *p_cached_grid = calloc(1, sizeof(*p_grid));
    p_cached_grid->width = p_grid->width;
    p_cached_grid->height = p_grid->height;
    p_cached_grid->buffer_size = p_grid->buffer_size;
    p_cached_grid->buffer = calloc(p_grid->buffer_size, sizeof(int));

    // Store cached grid in render_context
    p_render_context = calloc(1, sizeof(*p_render_context));
    p_render_context->p_cached_grid = p_cached_grid;
    p_render_context->frames_rendered = 0;

    // Initialize ncurses
    initscr();
    noecho();
    curs_set(0);
}

void renderer_update(grid* p_grid)
{

    // Iterate over grid and look for differences to cached_grid
    for (int i = 0; i < p_grid->buffer_size; i++)
    {
        // Difference was found, note that this character must be re-rendered
        if (p_grid->buffer[i] != p_render_context->p_cached_grid->buffer[i]) {

            // Compute row and column index of the character we need to re-render
            int pos_x = i % (p_render_context->p_cached_grid->width / group_width);
            int pos_y = i / (p_render_context->p_cached_grid->width / group_width);           

            // Obtain correct braille character
            char uc[5];
            int braille = lookup_table[p_grid->buffer[i]];
            int_to_unicode_char(braille, uc);

            // Render the braille character at the position that changed
            mvprintw(pos_y, pos_x, uc);
        }
    }

    // ToDo: Update p_cached_grid
    p_render_context->frames_rendered++;

    // Update cached buffer with current one
    memcpy(p_render_context->p_cached_grid->buffer, p_grid->buffer, sizeof(int) * p_grid->buffer_size);

    // Sleep some milliseconds so that changes are visible to the human eye
    napms(render_delay_ms);

    // Refresh terminal to render changes
    refresh();
}

void renderer_free()
{
    // Wait before all allocations are free'd
    napms(2000);

    // Free all allocations and end ncurses window
    free(p_render_context->p_cached_grid->buffer);
    free(p_render_context->p_cached_grid);
    free(p_render_context);
    endwin();
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