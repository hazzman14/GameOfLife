/**
 * Implements a class representing a 2d grid of cells.
 *      - New cells are initialized to Cell::DEAD.
 *      - Grids can be resized while retaining their contents in the remaining area.
 *      - Grids can be rotated, cropped, and merged together.
 *      - Grids can return counts of the alive and dead cells.
 *      - Grids can be serialized directly to an ascii std::ostream.
 *
 * You are encouraged to use STL container types as an underlying storage mechanism for the grid cells.
 *
 * @author 954519
 * @date March, 2020
 */


// Include the minimal number of headers needed to support your implementation.
// #include ...
#include "grid.h"
#include <vector>
#include <iostream>
#include <stdexcept>

/**
 * Grid::Grid()
 *
 * Construct an empty grid of size 0x0.
 * Can be implemented by calling Grid::Grid(square_size) constructor.
 *
 * @example
 *
 *      // Make a 0x0 empty grid
 *      Grid grid;
 *
 */
Grid::Grid() : Grid(0)
{
    //pass to square size constructor
}

/**
 * Grid::Grid(square_size)
 *
 * Construct a grid with the desired size filled with dead cells.
 * Single value constructors should be marked "explicit" to prevent them
 * being used to implicitly cast ints to grids on construction.
 *
 * Can be implemented by calling Grid::Grid(width, height) constructor.
 *
 * @example
 *
 *      // Make a 16x16 grid
 *      Grid x(16);
 *
 *      // Also make a 16x16 grid
 *      Grid y = Grid(16);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      Grid z = 16;
 *
 * @param square_size
 *      The edge size to use for the width and height of the grid.
 */
Grid::Grid(const unsigned int square_size) : Grid(square_size, square_size)
{
    //pass the width height constructor
}

/**
 * Grid::Grid(width, height)
 *
 * Construct a grid with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x9 grid
 *      Grid grid(16, 9);
 *
 * @param width
 *      The width of the grid.
 *
 * @param height
 *      The height of the grid.
 */

Grid::Grid(const unsigned int width, const unsigned int height) : width(width), height(height)
{
    //fill all cells with dead
    for (int y = 0; y < get_height(); y++)
    {
        for (int x = 0; x < get_width(); x++)
        {
            cell_grid.push_back(Cell::DEAD);
        }
    }
}

Grid::~Grid()
{
}

/**
 * Grid::get_width()
 *
 * Gets the current width of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the width of the grid to the console
 *      std::cout << grid.get_width() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the width of the grid to the console
 *      std::cout << read_only_grid.get_width() << std::endl;
 *
 * @return
 *      The width of the grid.
 */
int Grid::get_width() const
{
    return width;
}

/**
 * Grid::get_height()
 *
 * Gets the current height of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the height of the grid to the console
 *      std::cout << grid.get_height() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the height of the grid to the console
 *      std::cout << read_only_grid.get_height() << std::endl;
 *
 * @return
 *      The height of the grid.
 */
int Grid::get_height() const
{
    return height;
}

/**
 * Grid::get_total_cells()
 *
 * Gets the total number of cells in the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << grid.get_total_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << read_only_grid.get_total_cells() << std::endl;
 *
 * @return
 *      The number of total cells.
 */

unsigned int Grid::get_total_cells() const
{
    unsigned int total_cells = 0;
    //loop and increment total cells for every cell
    for (int y = 0; y < get_height(); y++)
    {
        for (int x = 0; x < get_width(); x++)
        {
            total_cells++;
        }
    }
    return total_cells;
}

/**
 * Grid::get_alive_cells()
 *
 * Counts how many cells in the grid are alive.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of alive cells to the console
 *      std::cout << grid.get_alive_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of alive cells to the console
 *      std::cout << read_only_grid.get_alive_cells() << std::endl;
 *
 * @return
 *      The number of alive cells.
 */
unsigned int Grid::get_alive_cells() const
{
    unsigned int alive_cells = 0;
    //loop and increment alive cells for every alive cell
    for (int y = 0; y < get_height(); y++)
    {
        for (int x = 0; x < get_width(); x++)
        {
            if (get(x, y) == Cell::ALIVE)
            {
                alive_cells++;
            }
        }
    }

    return alive_cells;
}

/**
 * Grid::get_dead_cells()
 *
 * Counts how many cells in the grid are dead.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of dead cells to the console
 *      std::cout << grid.get_dead_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of dead cells to the console
 *      std::cout << read_only_grid.get_dead_cells() << std::endl;
 *
 * @return
 *      The number of dead cells.
 */
unsigned int Grid::get_dead_cells() const
{
    unsigned int dead_cells = 0;
    //loop and incrememnt dead cells for every dead cell
    for (int y = 0; y < get_height(); y++)
    {
        for (int x = 0; x < get_width(); x++)
        {
            if (get(x, y) == Cell::DEAD)
            {
                dead_cells++;
            }
        }
    }

    return dead_cells;
}

/**
 * Grid::resize(square_size)
 *
 * Resize the current grid to a new width and height that are equal. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 8x8
 *      grid.resize(8);
 *
 * @param square_size
 *      The new edge size for both the width and height of the grid.
 */

void Grid::resize(unsigned int square_size)
{
    //pass to the other resize
    resize(square_size, square_size);
}
/**
 * Grid::resize(width, height)
 *
 * Resize the current grid to a new width and height. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 2x8
 *      grid.resize(2, 8);
 *
 * @param new_width
 *      The new width for the grid.
 *
 * @param new_height
 *      The new height for the grid.
 */

void Grid::resize(const unsigned int new_width, const unsigned int new_height)
{

    std::vector<Cell> temp;
    //loop through every cell of the new
    for (unsigned int y = 0; y < new_height; y++)
    {
        for (unsigned int x = 0; x < new_width; x++)
        {
            //if less than originals width and height pushback its values
            if (((int)x < get_width()) && ((int)y < get_height()))
            {
                temp.push_back(get(x, y));
            }
            //when its more start pushing dead cells
            else
            {
                temp.push_back(Cell::DEAD);
            }
        }
    }

    this->cell_grid = temp;
    this->width = new_width;
    this->height = new_height;
}

/**
 * Grid::get_index(x, y)
 *
 * Private helper function to determine the 1d index of a 2d coordinate.
 * Should not be visible from outside the Grid class.
 * The function should be callable from a constant context.
 *
 * @param x
 *      The x coordinate of the cell.
 *
 * @param y
 *      The y coordinate of the cell.
 *
 * @return
 *      The 1d offset from the start of the data array where the desired cell is located.
 */
unsigned int Grid::get_index(const unsigned int x, const unsigned int y) const
{
    //formula to go from 2d to 1d index
    return (x + get_width() * y);
}

/**
 * Grid::get(x, y)
 *
 * Returns the value of the cell at the desired coordinate.
 * Specifically this function should return a cell value, not a reference to a cell.
 * The function should be callable from a constant context.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Read the cell at coordinate (1, 2)
 *      Cell cell = grid.get(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @return
 *      The value of the desired cell. Should only be Grid::ALIVE or Grid::DEAD.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
Cell Grid::get(const int x, const int y) const
{
    if (x >= get_width() || x < 0 || y >= get_height() || y < 0)
    {
        throw std::out_of_range("get is out of bounds.");
    }
    else
    {
        return operator()(x, y);
    }
}

/**
 * Grid::set(x, y, value)
 *
 * Overwrites the value at the desired coordinate.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Assign to a cell at coordinate (1, 2)
 *      grid.set(1, 2, Cell::ALIVE);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @param value
 *      The value to be written to the selected cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */

void Grid::set(const int x, const int y, Cell value)
{
    operator()(x, y) = value;
}
/**
 * Grid::operator()(x, y)
 *
 * Gets a modifiable reference to the value at the desired coordinate.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = grid(1, 2);
 *
 *      // Directly assign to a cell at coordinate (1, 2)
 *      grid(1, 2) = Cell::ALIVE;
 *
 *      // Extract a reference to an individual cell to avoid calculating it's
 *      // 1d index multiple times if you need to access the cell more than once.
 *      Cell &cell_reference = grid(1, 2);
 *      cell_reference = Cell::DEAD;
 *      cell_reference = Cell::ALIVE;
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A modifiable reference to the desired cell.
 *
 * @throws
 *      std::runtime_error or sub-class if x,y is not a valid coordinate within the grid.
 */
Cell &Grid::operator()(const int x, const int y)
{
    if (x >= get_width() || y >= get_height() || x < 0 || y < 0)
    {
        throw std::runtime_error("Grid::operator() out of bounds.");
    }
    else
    {
        Cell &value = cell_grid.at(get_index(x, y));
        return value;
    }
}

/**
 * Grid::operator()(x, y)
 *
 * Gets a read-only reference to the value at the desired coordinate.
 * The operator should be callable from a constant context.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Constant reference to a grid (does not make a copy)
 *      const Grid &read_only_grid = grid;
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = read_only_grid(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A read-only reference to the desired cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
const Cell &Grid::operator()(const int x, const int y) const
{
    if (x >= get_width() || y >= get_height() || x < 0 || y < 0)
    {
        throw std::runtime_error("Grid::operator() out of bounds.");
    }
    else
    {
        const Cell &value = cell_grid.at(get_index(x, y));
        return value;
    }
   
}
/**
 * Grid::crop(x0, y0, x1, y1)
 *
 * Extract a sub-grid from a Grid.
 * The cropped grid spans the range [x0, x1) by [y0, y1) in the original grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid y(4, 4);
 *
 *      // Crop the centre 2x2 in y, trimming a 1 cell border off all sides
 *      Grid x = y.crop(x, 1, 1, 3, 3);
 *
 * @param x0
 *      Left coordinate of the crop window on x-axis.
 *
 * @param y0
 *      Top coordinate of the crop window on y-axis.
 *
 * @param x1
 *      Right coordinate of the crop window on x-axis (1 greater than the largest index).
 *
 * @param y1
 *      Bottom coordinate of the crop window on y-axis (1 greater than the largest index).
 *
 * @return
 *      A new grid of the cropped size containing the values extracted from the original grid.
 *
 * @throws
 *      std::exception or sub-class if x0,y0 or x1,y1 are not valid coordinates within the grid
 *      or if the crop window has a negative size.
 */
Grid Grid::crop(const int x0, const int y0, const int x1, const int y1) const
{
    if (x0 < 0 || x0 > x1 || y0 < 0 || y0 > y1 || x1 > get_width() || y1 > get_height())
    {
        throw std::out_of_range("crop out of bounds.");
    }
    else
    {
        std::vector<Cell> temp;
        unsigned int diffx = x1 - x0;
        unsigned int diffy = y1 - y0;
        Grid newGrid = Grid(diffx, diffy);
        //loop crop coordinates and pushback value
        for (int y = y0; y < y1; y++)
        {
            for (int x = x0; x < x1; x++)
            {
                temp.push_back(get(x, y));
            }
        }

        newGrid.cell_grid = temp;
        return newGrid;
    }
}

/**
 * Grid::merge(other, x0, y0, alive_only = false)
 *
 * Merge two grids together by overlaying the other on the current grid at the desired location.
 * By default merging overwrites all cells within the merge reason to be the value from the other grid.
 *
 * Conditionally if alive_only = true perform the merge such that only alive cells are updated.
 *      - If a cell is originally dead it can be updated to be alive from the merge.
 *      - If a cell is originally alive it cannot be updated to be dead from the merge.
 *
 * @example
 *
 *      // Make two grids
 *      Grid x(2, 2), y(4, 4);
 *
 *      // Overlay x as the upper left 2x2 in y
 *      y.merge(x, 0, 0);
 *
 *      // Overlay x as the bottom right 2x2 in y, reading only alive cells from x
 *      y.merge(x, 2, 2, true);
 *
 * @param other
 *      The other grid to merge into the current grid.
 *
 * @param x0
 *      The x coordinate of where to place the top left corner of the other grid.
 *
 * @param y0
 *      The y coordinate of where to place the top left corner of the other grid.
 *
 * @param alive_only
 *      Optional parameter. If true then merging only sets alive cells to alive but does not explicitly set
 *      dead cells, allowing whatever value was already there to persist. Defaults to false.
 *
 * @throws
 *      std::exception or sub-class if the other grid being placed does not fit within the bounds of the current grid.
 */
void Grid::merge(const Grid other, const int x0, const int y0, const bool alive_only)
{

    if (x0 < 0 || x0 + other.get_width() > get_width() || y0 < 0 || y0 + other.get_height() > get_height())
    {
        throw std::out_of_range("merge out of bounds.");
    }
    else
    {
        //loop through start of new grid to end
        for (int y = y0; y < y0 + other.get_height(); y++)
        {
            for (int x = x0; x < x0 + other.get_width(); x++)
            {
                if (alive_only == true)
                {
                    //if alive set alive otherwise set it to others value
                    if (other.get(x - x0, y - y0) == Cell::ALIVE)
                    {
                        set(x, y, Cell::ALIVE);
                    }
                }
                else
                {
                    set(x, y, other.get(x - x0, y - y0));
                }
            }
        }
    }
}

/**
 * Grid::rotate(rotation)
 *
 * Create a copy of the grid that is rotated by a multiple of 90 degrees.
 * The rotation can be any integer, positive, negative, or 0.
 * The function should take the same amount of time to execute for any valid integer input.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a 1x3 grid
 *      Grid x(1,3);
 *
 *      // y is size 3x1
 *      Grid y = x.rotate(1);
 *
 * @param _rotation
 *      An positive or negative integer to rotate by in 90 intervals.
 *
 * @return
 *      Returns a copy of the grid that has been rotated.
 */
Grid Grid::rotate(const int _rotation) const
{

    int number_of_rotations = ((_rotation % 4) + 4) % 4;
    int new_width;
    int new_height;

    //switch width and height if 90 or 270 degrees
    if (number_of_rotations == 1 || number_of_rotations == 3)
    {       
        new_width = get_height();
        new_height = get_width();
    }
    else
    {
        //360 or 0 degrees
        //dont switch
        new_width = get_width();
        new_height = get_height();
    }

    Grid new_grid = Grid(new_width, new_height);

    //loop through every cell of newgrid
    for (int y = 0; y < new_height; y++)
    {
        for (int x = 0; x < new_width; x++)
        {
            //make a cell to hold rotated value
            Cell rotated_cell;
            if (number_of_rotations == 0)
            {
                //do nothing if no rotation
                rotated_cell = operator()(x, y);
            }
            else if (number_of_rotations == 1)
            {
                //(x,y)->(y,-x)
                rotated_cell = operator()(y,new_width-1 -x);
            }
            else if (number_of_rotations == 2)
            {
                //(x,y)->(-y,-x)
                rotated_cell = operator()(new_width-1 -x, new_height -1 -y);
            }
            else if (number_of_rotations == 3)
            {
                //(x,y)->(y,x)
                rotated_cell = operator()(new_height-1 -y, x);
            }     
            new_grid(x,y)=rotated_cell; 
        }

    }
    return new_grid;
}

/**
 * operator<<(output_stream, grid)
 *
 * Serializes a grid to an ascii output stream.
 * The grid is printed wrapped in a border of - (dash), | (pipe), and + (plus) characters.
 * Alive cells are shown as # (hash) characters, dead cells with ' ' (space) characters.
 *
 * The function should be callable on a constant Grid.
 *
 * @example
 *
 *      // Make a 3x3 grid with a single alive cell
 *      Grid grid(3);
 *      grid(1, 1) = Cell::ALIVE;
 *
 *      // Print the grid to the console
 *      std::cout << grid << std::endl;
 *
 *      // The grid is printed with a border of + - and |
 *
 *      +---+
 *      |   |
 *      | # |
 *      |   |
 *      +---+
 *
 * @param os
 *      An ascii mode output stream such as std::cout.
 *
 * @param grid
 *      A grid object containing cells to be printed.
 *
 * @return
 *      Returns a reference to the output stream to enable operator chaining.
 */

std::ostream &operator<<(std::ostream &os, const Grid &grid)
{
    //first line
    os << "+";
    for (int i = 0; i < (grid.get_width()); i++)
    {
        os << "-";
    }
    os << "+";
    os << "\n";

    //main body
    for (int y = 0; y < grid.get_height(); y++)
    {
        os << "|";
        for (int x = 0; x < grid.get_width(); x++)
        {

            if (grid.get(x, y) == Cell::ALIVE)
            {
                os << '#';
            }
            else
            {
                os << ' ';
            }
        }
        os << "|";
        os << "\n";
    }

    //final line
    os << "+";
    for (int i = 0; i < (grid.get_width()); i++)
    {
        os << "-";
    }
    os << "+";
    os << "\n";

    return os;
}