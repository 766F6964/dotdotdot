# DotDotDot
## Overview

[![License: LGPL v3](https://img.shields.io/badge/License-LGPL%20v3-blue.svg)](https://www.gnu.org/licenses/lgpl-3.0)

DotDotDot is a performant library that uses braille characters to draw to the terminal in a user-defined grind.
It is not limited to rendering a single image, but also allows for smooth animations.
DotDotDot is developed for linux, but should also work on MacOSX (not tested). Windows is not supported.

**Important:** Make sure your terminal uses a font that supports braille unicode characters, otherwise the output will look messed up!

## Features
- Rendering engine for animations
- Efficient (Minimal memory footprint, caching ...)
- Intuitive API to modify the grid
    - Draw individual dots/pixels
    - Draw basic geometic shapes (triangle, lines ...)
    - Draw borders around the grid 

## Usage & examples
The repository includes some examples what the library can do. They can be found under `examples/examples.c`.
Shown below is the example to track an animated sine curve:

![](https://i.imgur.com/bS5iAUP.gif)

```csharp
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
```

## Dependencies
- `libm` for mathematical functions
- `ncurses` needed by the renderer

## Roadmap
- Improve rendering performance
- Add additional shapes/structures to the API
- Framepacing measurement/correction for animations
- A statusbar that can display additional information such as frames per second etc.
- Unit tests

## Troubleshooting
The most common problem when working with dotdotdot is that the braille characters are not correctly displayed in the terminal.
There are three possible causes for this:

**Fonts:**
Make sure you have a font installed that supports braille characters.
You can either install a font that has braille support, for example Terminus or DejaVuSansMono. 
Alternatively, you can directly download a braille ttf file from here: http://www.wazu.jp/gallery/Fonts_Braille.html
And then install it by following your linux distributions guidelines on how to install fonts.

**Terminal:**
Not all terminals appear to work correctly when it comes to displaying braille characters.
Terminals that are confirmed working are: st, rxvt-unicode.
Terminals that are known to cause issues (e.g. printing gibberish), are: konsole, xterm.

**Locales:**
Make sure your locales are setup correctly on your system. There have been problems when those were not setup correctly.
If that is the case, you can also try changing the `setlocale(LC_ALL, "")` from a blank one to any UTF-8 one, such `en_US.UTF-8`.

## References
The project was heavily inspired by the popular ![drawille library](https://github.com/asciimoo/drawille).
