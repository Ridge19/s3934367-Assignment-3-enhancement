#ifndef GENERATE_MAZE_H
#define GENERATE_MAZE_H

#include <iostream>
#include <random>
#include <mcpp/mcpp.h>
#include <random>
#include <vector>

using std::vector;

class GenerateMaze {
public:
    //default constructor
    GenerateMaze(unsigned int x_min, unsigned int x_max, unsigned int z_min, unsigned int z_max, mcpp::Coordinate basePoint); 
    GenerateMaze() : mc(), basePoint(0, 0, 0), xlen(0), zlen(0),
                    x_min(0), x_max(0), z_min(0), z_max(0) {
    }
    // destructor
    ~GenerateMaze();
    
    void PrintMaze(int rows, int columns); //print maze?? 
    bool checkMaze(unsigned int xlen, unsigned int zlen); //checks if maze is < 3
    void Recursive(std::vector<std::vector<char>>& structure, unsigned int startRow, unsigned int endRow, unsigned int startCol, unsigned int endCol, std::mt19937& gen); //recursive division algorithm
private:

    mcpp::MinecraftConnection mc;
    mcpp::Coordinate basePoint;

    unsigned int rows;
    unsigned int cols;

    unsigned int xlen;
    unsigned int zlen;

    unsigned int x_min;
    unsigned int x_max;
    unsigned int z_min;
    unsigned int z_max;
};

#endif //GENERATE_MAZE_H