/**
 * Declares a class representing a 2d grid of cells.
 * Rich documentation for the api and behaviour the Grid class can be found in grid.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 954519
 * @date March, 2020
 */
#pragma once

// Add the minimal number of includes you need in order to declare the class.
// #include ...
#include <vector>
#include <ostream>
/**
 * A Cell is a char limited to two named values for Cell::DEAD and Cell::ALIVE.
 */
enum Cell : char
{
    DEAD = ' ',
    ALIVE = '#'
};

/**
 * Declare the structure of the Grid class for representing a 2d grid of cells.
 */
class Grid
{
private:
    unsigned int width;
    unsigned int height;
    std::vector<Cell> cell_grid;
    unsigned int get_index(const unsigned int x, const unsigned int y) const;

public:
    Grid();
    explicit Grid(const unsigned int square_size);
    Grid(const unsigned int width, const unsigned int height);
    ~Grid();

    int get_width() const;
    int get_height() const;
    unsigned int get_total_cells() const;
    unsigned int get_alive_cells() const;
    unsigned int get_dead_cells() const;

    void resize(const unsigned int square_size);
    void resize(const unsigned int width, const unsigned int height);

    Cell get(const int x, const int y) const;

    void set(const int x, const int y, Cell value);

    Cell &operator()(const int x, const int y);
    const Cell &operator()(const int x, const int y) const;

    Grid crop(const int x0, const int y0, const int x1, const int y1) const;

    void merge(const Grid other, const int x0, const int y0, const bool alive_only = false);

    Grid rotate(const int _rotation) const;

    friend std::ostream &operator<<(std::ostream &os, const Grid &grid);
    // How to draw an owl:
    //     Step 1. Draw a circle.
    //     Step 2. Draw the rest of the owl.
};