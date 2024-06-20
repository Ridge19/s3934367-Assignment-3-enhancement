#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <ctime>

#include <mcpp/mcpp.h>
#include "GenerateMaze.h" // generate maze file
#include <time.h>


// default constructor???
GenerateMaze::GenerateMaze(unsigned int x_min, unsigned int x_max, unsigned int z_min, unsigned int z_max, mcpp::Coordinate basePoint) {
    this->x_min = x_min;
    this->x_max = x_max;
    this->z_min = z_min;
    this->z_max = z_max;
    this->basePoint = basePoint;
    xlen = x_max - x_min;
    zlen = z_max - z_min;
}

// destructor
GenerateMaze::~GenerateMaze() {
}


bool GenerateMaze::checkMaze(unsigned int xlen, unsigned int zlen) {
    // base case - if maze L or W < 3
    if (xlen < 3 || zlen < 3) {
        return false;
    } else {
        return true;
    }
}


void GenerateMaze::Recursive(std::vector<std::vector<char>>& structure, unsigned int startRow, unsigned int endRow, unsigned int startCol, unsigned int endCol, std::mt19937& gen) {
    // Base case: if any dimension is too small, return
    // purpose: prevents infinite recursion and defines a stopping condition
    if (startRow >= endRow || startCol >= endCol) {
        return;
    }

    // Calculate the dimensions of the current area
    unsigned int height = endRow - startRow + 1;
    unsigned int width = endCol - startCol + 1;

    // Determine whether to divide horizontally or vertically based on larger dimension
    bool divideHorizontally = (width > height);

    // If dimensions are equal, choose randomly
    if (width == height) {
        std::uniform_int_distribution<> dis(0, 1);
        divideHorizontally = dis(gen) == 1;
    }

    // Calculate the position of the dividing wall
    unsigned int wallPosition;
    if (divideHorizontally) {
        // Choose a random odd point for horizontal division
        unsigned int availableRows = (endRow - startRow) / 2;
        if (availableRows <= 0) {
            return; // Cannot divide further horizontally
        }
        std::uniform_int_distribution<> rowDis(0, availableRows - 1);
        wallPosition = startRow + 1 + 2 * rowDis(gen);

        // Place the horizontal wall
        std::uniform_int_distribution<> colDis(startCol, endCol);
        unsigned int passageCol = colDis(gen);
        for (unsigned int j = startCol; j <= endCol; ++j) {
            if (wallPosition >= startRow && wallPosition <= endRow && j >= startCol && j <= endCol) {
                structure[wallPosition][j] = 'x';
            }
        }
        structure[wallPosition][passageCol] = '.';
        
        // Recursively divide the two sub-areas
        Recursive(structure, startRow, wallPosition - 1, startCol, endCol, gen); // Upper sub-area
        Recursive(structure, wallPosition + 1, endRow, startCol, endCol, gen);   // Lower sub-area

    } else {
        // Choose a random even point for vertical division
        unsigned int availableCols = (endCol - startCol) / 2;
        if (availableCols <= 0) {
            return; // Cannot divide further vertically
        }
        std::uniform_int_distribution<> colDis(0, availableCols - 1);
        wallPosition = startCol + 1 + 2 * colDis(gen);

        // Place the vertical wall
        std::uniform_int_distribution<> rowDis(startRow, endRow);
        unsigned int passageRow = rowDis(gen);
        for (unsigned int i = startRow; i <= endRow; ++i) {
            if (i >= startRow && i <= endRow && wallPosition >= startCol && wallPosition <= endCol) {
                structure[i][wallPosition] = 'x';
            }
        }
        structure[passageRow][wallPosition] = '.';
        
        // Recursively divide the two sub-areas
        Recursive(structure, startRow, endRow, startCol, wallPosition - 1, gen); // Left sub-area
        Recursive(structure, startRow, endRow, wallPosition + 1, endCol, gen);   // Right sub-area
    }
}

void GenerateMaze::PrintMaze(int rows, int columns) {
        // Seed the random number generator
    std::mt19937 gen(std::time(nullptr));

    // Create a 2D vector to store the structure
    std::vector<std::vector<char>> structure(rows, std::vector<char>(columns, '.'));

    // Place the borders
    for (int i = 0; i < rows; ++i) {
        structure[i][0] = 'x';
        structure[i][columns - 1] = 'x';
    }
    for (int j = 0; j < columns; ++j) {
        structure[0][j] = 'x';
        structure[rows - 1][j] = 'x';
    }

    // Start recursive division to generate the maze
    Recursive(structure, 1, rows - 2, 1, columns - 2, gen); // Start with inner area, leaving border intact

    structure[0][1] = '.'; // Entrance
    // Print the structure
    for (const auto& row : structure) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
}



