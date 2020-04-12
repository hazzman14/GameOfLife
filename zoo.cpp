/**
 * Implements a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 *      - Creatures like gliders, light weight spaceships, and r-pentominos can be spawned.
 *          - These creatures are drawn on a Grid the size of their bounding box.
 *
 *      - Grids can be loaded from and saved to an ascii file format.
 *          - Ascii files are composed of:
 *              - A header line containing an integer width and height separated by a space.
 *              - followed by (height) number of lines, each containing (width) number of characters,
 *                terminated by a newline character.
 *              - (space) ' ' is Cell::DEAD, (hash) '#' is Cell::ALIVE.
 *
 *      - Grids can be loaded from and saved to an binary file format.
 *          - Binary files are composed of:
 *              - a 4 byte int representing the grid width
 *              - a 4 byte int representing the grid height
 *              - followed by (width * height) number of individual bits in C-style row/column format,
 *                padded with zero or more 0 bits.
 *              - a 0 bit should be considered Cell::DEAD, a 1 bit should be considered Cell::ALIVE.
 *
 * @author YOUR_STUDENT_NUMBER
 * @date March, 2020
 */


// Include the minimal number of headers needed to support your implementation.
// #include ...
#include "grid.h"
#include "world.h"
#include "zoo.h"
#include <fstream>
#include <iostream>
#include <bitset>
#include <math.h>
#include <stdexcept>

/**
 * Zoo::glider()
 *
 * Construct a 3x3 grid containing a glider.
 * https://www.conwaylife.com/wiki/Glider
 *
 * @example
 *
 *      // Print a glider in a Grid the size of its bounding box.
 *      std::cout << Zoo::glider() << std::endl;
 *
 *      +---+
 *      | # |
 *      |  #|
 *      |###|
 *      +---+
 *
 * @return
 *      Returns a Grid containing a glider.
 */
    Grid Zoo::glider(){
        Grid glider(3,3);
        glider.set(1,0,Cell::ALIVE);
        glider.set(2,1,Cell::ALIVE);
        glider.set(0,2,Cell::ALIVE);
        glider.set(1,2,Cell::ALIVE);
        glider.set(2,2,Cell::ALIVE);
        return glider;
    }

/**
 * Zoo::r_pentomino()
 *
 * Construct a 3x3 grid containing an r-pentomino.
 * https://www.conwaylife.com/wiki/R-pentomino
 *
 * @example
 *
 *      // Print an r-pentomino in a Grid the size of its bounding box.
 *      std::cout << Zoo::r_pentomino() << std::endl;
 *
 *      +---+
 *      | ##|
 *      |## |
 *      | # |
 *      +---+
 *
 * @return
 *      Returns a Grid containing a r-pentomino.
 */
    Grid Zoo::r_pentomino(){
        Grid r_pentomino(3,3);
        r_pentomino.set(1,0,Cell::ALIVE);
        r_pentomino.set(2,0,Cell::ALIVE);
        r_pentomino.set(0,1,Cell::ALIVE);
        r_pentomino.set(1,1,Cell::ALIVE);
        r_pentomino.set(1,2,Cell::ALIVE);
        return r_pentomino;
    }

/**
 * Zoo::light_weight_spaceship()
 *
 * Construct a 5x4 grid containing a light weight spaceship.
 * https://www.conwaylife.com/wiki/Lightweight_spaceship
 *
 * @example
 *
 *      // Print a light weight spaceship in a Grid the size of its bounding box.
 *      std::cout << Zoo::light_weight_spaceship() << std::endl;
 *
 *      +-----+
 *      | #  #|
 *      |#    |
 *      |#   #|
 *      |#### |
 *      +-----+
 *
 * @return
 *      Returns a grid containing a light weight spaceship.
 */
    Grid Zoo::light_weight_spaceship(){
        Grid light_weight_spaceship(5,4);
        light_weight_spaceship.set(1,0,Cell::ALIVE);
        light_weight_spaceship.set(4,0,Cell::ALIVE);
        light_weight_spaceship.set(0,1,Cell::ALIVE);
        light_weight_spaceship.set(0,2,Cell::ALIVE);
        light_weight_spaceship.set(4,2,Cell::ALIVE);
        light_weight_spaceship.set(0,3,Cell::ALIVE);
        light_weight_spaceship.set(1,3,Cell::ALIVE);
        light_weight_spaceship.set(2,3,Cell::ALIVE);
        light_weight_spaceship.set(3,3,Cell::ALIVE);
        return light_weight_spaceship;
    }

/**
 * Zoo::load_ascii(path)
 *
 * Load an ascii file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an ascii file from a directory
 *      Grid grid = Zoo::load_ascii("path/to/file.gol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The parsed width or height is not a positive integer.
 *          - Newline characters are not found when expected during parsing.
 *          - The character for a cell is not the ALIVE or DEAD character.
 */
    Grid Zoo::load_ascii(std::string path){
        std::ifstream inputFile(path);
        if(!inputFile){
            throw std::runtime_error("file doesnt exist");
        }else{
            int width;
            int height;
                
            inputFile >> width;
            inputFile >> height;
            if(width<0||height<0){
                throw std::runtime_error("size out of bounds");
            }else{
                std::string line;
                getline(inputFile,line);
                    //make the grid
                    Grid ascii_grid(width,height);
                    //manipulate each line
                    for(int i = 0; i < height; i++){
                        getline(inputFile,line);
                        if((int)line.length()>width){
                        throw std::runtime_error("new line expected");
                        }else{
                            for(int j = 0; j < width; j++){
                                if(line.substr(j,1) == "#"){
                                    ascii_grid.set(j,i,Cell::ALIVE);
                                } else if(line.substr(j,1) == " "){
                                    ascii_grid.set(j,i,Cell::DEAD);
                                }else{
                                    throw std::runtime_error("unexpected character");
                                }
                            }
                        }
                    }
                return ascii_grid;
            }

        }

    }

/**
 * Zoo::save_ascii(path, grid)
 *
 * Save a grid as an ascii .gol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an ascii file in a directory
 *      try {
 *          Zoo::save_ascii("path/to/file.gol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
    void Zoo::save_ascii(std::string path, Grid grid){
        std::ofstream outputFile(path,std::ofstream::out);

        //put the width and height at the top with a space
        outputFile << grid.get_width() << " " << grid.get_height();

        for(unsigned int i = 0; i < grid.get_height(); i++){
            //new line every height change
            outputFile << "\n";
            for(unsigned int j = 0; j < grid.get_width(); j++){
                if(grid.get(j,i)==Cell::ALIVE){
                    outputFile << '#';
                } else{
                    outputFile << ' ';
                }
                
            }
        }
        //final new line added at the end
        outputFile << "\n";
    }

/**
 * Zoo::load_binary(path)
 *
 * Load a binary file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an binary file from a directory
 *      Grid grid = Zoo::load_binary("path/to/file.bgol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The file ends unexpectedly.
 */
    Grid Zoo::load_binary(std::string path){

        std::ifstream inputFile(path);

        //find length of file
        inputFile.seekg(0,inputFile.end);
        int length = inputFile.tellg();

        //set to beginning
        inputFile.seekg(0,inputFile.beg);
    
        char buffer[length];

        //start after width and height (8 bytes)
        inputFile.read(buffer,8);
        
        //get width and height, 4 bytes each
        int width = buffer[0];
        int height = buffer[4];
       
        //make the grid
        Grid binary_grid(width,height);
        //make vector
        std::vector<Cell> cells;

        // 36/8 = 4.5 bytes round to 5, last 4 bits not needed(padding)
        double decimal =(double)(width*height)/8;
        int number_of_bytes = ceil(decimal);

        //loop through bits, checking value and pushing to vector
        for(int i = 0; i <number_of_bytes; i++){
            //store byte values into bitset
            std::bitset<8> bits(inputFile.get());
            //go through each bit and push to vector
            for(int j = 0; j <8; j++){
                if(bits.test(j)){
                    cells.push_back(Cell::ALIVE);
                }else{
                    cells.push_back(Cell::DEAD);
                }
            }
        }
        //set the grid with vectors values
        for(unsigned int i = 0; i < binary_grid.get_height();i++){
            for(unsigned int j = 0; j < binary_grid.get_width();j++){
                binary_grid.set(j,i,cells.at(j+width*i));
            }
        }
        
        inputFile.close();
        return binary_grid;
    }

/**
 * Zoo::save_binary(path, grid)
 *
 * Save a grid as an binary .bgol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an binary file in a directory
 *      try {
 *          Zoo::save_binary("path/to/file.bgol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
    void Zoo::save_binary(std::string path, Grid grid){
       
        std::ofstream outputFile(path);
        int width = grid.get_width();
        int height = grid.get_height();
        //put width and height in
        outputFile.write((char*)&width,4);
        outputFile.write((char*)&height,4);
        std::bitset<8> bits;
        int counter = 0;
        //loop through all values, if alive set nth value of bitset to 1 else 0
        for(unsigned int i = 0; i < grid.get_height();i++){
            for(unsigned int j = 0; j < grid.get_width();j++){ 
                if(grid.get(j,i)==Cell::ALIVE){
                    bits.set(counter,1); 
                } else{
                    bits.set(counter,0);
                }
                //when counter is 7 the bitset is full, write it to file and reset counter
                if (counter == 7){
                    outputFile.write((char*)&bits,1);
                    counter=0;
                }else{
                    counter++;
                }
            }
        }
        //when you need to pad out the last bitset
        if(counter != 0){
            //loop from wherever it stopped to the end
            for(int i = counter;i<7;i++){
                //if the bitset is being padded with negative set it to 0 else 1
                if(bits.test(counter-1)==0){
                    bits.set(i,0);
                }else{
                    bits.set(i,1);
                }
                outputFile.write((char*)&bits,1);
            }
        }
    }

