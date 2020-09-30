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

    // Generate braille lookup table
    grid_generate_lookup_table();

    // Set locale for ncurses to process unicode correctly
    setlocale(LC_ALL, "");

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

void renderer_raw_dump(grid* p_grid)
{
    for (int i = 0; i < p_grid->buffer_size; i++)
    {
	// Obtain correct braille character
	char uc[5];
	int braille = lookup_table[p_grid->buffer[i]];

	if(BRAILLE_BLANK == braille) {
	    uc[0] = ' ';
	    uc[1] = '\0';
	} else {
	    // int to UTF8 is more accurate
	    int_to_unicode_char(braille, uc);
	}

	// UTF8 is safe to just print (no internal '\0's)
	printf("%s", uc);

	// Linebreak if we reached the right end of the grid
	if (i % (p_grid->width / group_width) == 0 && i != 0)
	{
	    printf("\n");
	}
    }
    printf("\n");
}

void renderer_update(grid* p_grid)
{
    // Notes:
    // Should only render the characters that changed from current grid buffer to the cached one
 
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

            // Linebreak if we reached the right end of the grid
            if (i % (p_grid->width / group_width) == 0 && i != 0)
            {
                printw("\n");
            }

            // Render the braille character at the position that changed
            mvprintw(pos_y, pos_x, uc);

            //printw("Change index %i [%i->%i] Rerendering coordinate (%i, %i).\n", i, p_render_context->p_cached_grid->buffer[i], p_grid->buffer[i], pos_x, pos_y);
        }
    }

    // ToDo: Update p_cached_grid
    p_render_context->frames_rendered++;

    //grid_print_buffer(p_render_context->p_cached_grid, "cached: ");
    //grid_print_buffer(p_grid, "current: ");

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
