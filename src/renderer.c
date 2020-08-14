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
    curs_set(FALSE);
}

void renderer_update(grid* p_grid)
{
    // (!! Buggy !!) 
    // Only render the characters that changed from current grid to cached grid

    //printf("Rendering frame %i\n", p_render_context->frames_rendered);
    //grid_print_buffer(p_grid, "Current: ");
    //grid_print_buffer(p_render_context->p_cached_grid, "Cached : ");

    // Iterate over grid and look for differences to cached_grid
    for (int i = 0; i < p_grid->buffer_size; i++)
    {
        // Difference was found, note that this character must be re-rendered
        if (p_grid->buffer[i] != p_render_context->p_cached_grid->buffer[i]) {

            // Compute row and column index of the character we need to re-render
            //int pos_x = i % (p_render_context->p_cached_grid->width / group_width);
            //int pos_y = i / (p_render_context->p_cached_grid->width / group_width);
            
            //move();
            //mvdelch(pos_y, pos_x);

            //printf("Change index %i [%i->%i] Rerendering coordinate (%i, %i).\n", i, p_render_context->p_cached_grid->buffer[i], p_grid->buffer[i], pos_x, pos_y);
        }
    }

    // Clear all changes from the previous screen
    // This is a dirty hack, - ideally we want to render only the characters that changed
    // from the cached frame to the current frame, which is what the code above tried to attempt
    // However it does not yet work correctly, because overwriting characters at specific coordinates causes problems
    erase();

    // Render current frame
    for (int i = 0; i < p_grid->buffer_size; ++i)
    {
        char uc[5];
        int braille = lookup_table[p_grid->buffer[i]];
        int_to_unicode_char(braille, uc);

        if (i % (p_grid->width / group_width) == 0 && i != 0)
        {
            printw("\n");
        }
        printw(uc);
    }
    printw("\n");

    // ToDo: Update p_cached_grid
    p_render_context->frames_rendered++;

    // Sleep some milliseconds so that changes are visible to the human eye
    napms(render_delay_ms);

    // Refresh terminal to render changes
    refresh();
}

void renderer_free()
{
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