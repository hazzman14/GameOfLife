/**
 * Declares a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 * Rich documentation for the api and behaviour the Zoo namespace can be found in zoo.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 954519
 * @date March, 2020
 */
#pragma once

// Add the minimal number of includes you need in order to declare the namespace.
// #include ...
#include "grid.h"
/**
 * Declare the interface of the Zoo namespace for constructing lifeforms and saving and loading them from file.
 */
namespace Zoo
{

Grid glider();
Grid r_pentomino();
Grid light_weight_spaceship();

Grid load_ascii(const std::string path);
void save_ascii(const std::string path, const Grid grid);

Grid load_binary(const std::string path);
void save_binary(const std::string path, const Grid grid);

// How to draw an owl:
//      Step 1. Draw a circle.
//      Step 2. Draw the rest of the owl.

}; // namespace Zoo