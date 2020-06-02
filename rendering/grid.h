//
// Created by void on 5/31/20.
//

#ifndef DOTS_GRID_H
#define DOTS_GRID_H


#include <vector>

class grid {
public:

    /// Initializes a new grid with the given dimensions
    /// \param width The width of the grid in braille pixels
    /// \param height The height of the grid in braille pixels
    grid(int width, int height);

    /// Clears all braille pixels in the grid
    void clear();

    /// Fills the entire grid with braille pixels
    void fill();

    /// Sets a braille pixel in the grid at the specified coordinate
    /// \param x The x coordinate of the pixel
    /// \param y The y coordinate of the pixel
    void set_pixel(int x, int y);

    /// Clears a braille pixel in the grid at the specified coordinate
    /// \param x The x coordinate of the pixel
    /// \param y The y coordinate of the pixel
    void unset_pixel(int x, int y);

    /// Checks if a braille pixel is set at the specified coordinate
    /// \param x The x coordinate to check
    /// \param y The y coordinate to check
    /// \return true if the pixel is set, otherwise false
    bool is_set(int x, int y);

    /// Gets the width of the grid in braille pixels
    /// \return The width of the grid
    int get_width() const;

    /// Gets the height of the grid in braille pixels
    /// \return The height of the grid
    int get_height() const;

    /// Gets the size of the drawing buffer
    /// \return
    int get_buffer_size();

    /// Renders the entire grid to the console
    void render();

private:

    /// Checks that a specified coordinate is inside the grid
    /// \param x The x coordinate to check
    /// \param y The y coordinate to check
    void validate_coordinates(int x, int y) const;

    /// Changes a pixel to be either set or unset
    /// \param x The x coordinate of the pixel
    /// \param y The y coordinate of the pixel
    /// \param value true if the pixel should be set and false if the pixel should be unset
    void modify_pixel(int x, int y, int value);

    /// Generates a table of all braille character permutations
    void generate_lookup_table();

    /// Converts the compressed buffer value into a braille character
    /// \param code The compressed buffer value that represents a single braille character
    /// \param chars The buffer to write the unicode value to
    void int_to_unicode_char(unsigned int code, char *chars);

    /// The starting offset of braille unicode character
    const int BRAILLE_OFFSET = 0x2800;

    /// The transformation matrix that is used to convert the grid position to the braille offset
    /// More information can be found at: https://en.wikipedia.org/wiki/Braille_Patterns
    const int TRANSFORMATION_MATRIX[8] = {0x01, 0x02, 0x04, 0x40, 0x08, 0x10, 0x20, 0x80};

    /// The lookup table that stores all braille permutations
    wchar_t lookup_table[256]{};

    /// The width of the grid in braille pixels
    int grid_width;

    /// The height of the grid in braille pixels
    int grid_height;

    /// The amount of dots that describe the width of a braille character
    const int group_width = 2;

    /// The amount of dots that describe the height of a braille character
    const int group_height = 4;

    /// The drawing buffer that stores the braille characters in a compressed form
    std::vector<int> buffer;

};


#endif //DOTS_GRID_H
