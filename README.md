# DotDotDot
## Overview
DotDotDot is a performant library that uses braille characters to draw to the terminal.
It is not limited to rendering a single image, but also allows for animations.

## Features
- Comes with a rendering engine that supports animations
- Minimal memory footprint
- Very easy usage by accessing the canvas with coordinates

## Examples
An example of what can be done with this library:

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

## References
The project was heavily inspired by the popular ![drawille library](https://github.com/asciimoo/drawille).