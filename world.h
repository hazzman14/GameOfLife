/**
 * Declares a class representing a 2d grid world for simulating a cellular automaton.
 * Rich documentation for the api and behaviour the World class can be found in world.cpp.
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
#include "grid.h"
/**
 * Declare the structure of the World class for representing a 2d grid world.
 *
 * A World holds two equally sized Grid objects for the current state and next state.
 *      - These buffers should be swapped using std::swap after each update step.
 */
class World
{
private:
    Grid current_grid;
    Grid next_grid;
    unsigned int count_neighbours(const int x, const int y, const bool toroidal);

public:
    World();
    explicit World(const unsigned int square_size);
    World(const unsigned int width, const unsigned int height);
    World(Grid initial_state);
    ~World();

    int get_width() const;
    int get_height() const;
    unsigned int get_total_cells() const;
    unsigned int get_alive_cells() const;
    unsigned int get_dead_cells() const;

    const Grid &get_state() const;

    void resize(const unsigned int square_size);
    void resize(const unsigned int new_width, const unsigned int new_height);

    void step(const bool toroidal = false);
    
    void advance(const unsigned int steps, const bool toroidal = false);
    // How to draw an owl:
    //      Step 1. Draw a circle.
    //      Step 2. Draw the rest of the owl.
};