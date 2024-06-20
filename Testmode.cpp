#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// #include <mcpp/mcpp.h> // Minecraft library, not needed for this example
#include "testmode.h"
#include "GenerateMaze.h"

// Function prototype for GenerateMazeTest
void GenerateMazeTest(int rows, int columns);

void TestMode::GenerateMazeTest(int rows, int columns) {
    // Corrected call to the global GenerateMazeTest function
    ::GenerateMazeTest(rows, columns);
}

// generates structure for testmode 
void GenerateStructureTest(std::vector<std::vector<char>>& structure, int startRow, int endRow, int startCol, int endCol, bool lastDivisionHorizontal) {
    if (startRow >= endRow || startCol >= endCol) {
        return;
    }

    int height = endRow - startRow + 1;
    int width = endCol - startCol + 1;

    //lastdivisionhorizontal variable keeps track of the last division method
    bool divideHorizontally = !lastDivisionHorizontal;
    if (width == height) {
        divideHorizontally = true;
    }

    // calculating if dividing horizontally or vertically
    int wallPosition;
    if (divideHorizontally) {
        int availableRows = (endRow - startRow) / 2;
        if (availableRows <= 0) {
            return;
        }
        wallPosition = startRow + 1 + 2 * (std::rand() % availableRows); // place wall position in a random odd row
        if (wallPosition < startRow || wallPosition > endRow) {
            return;
        }
        for (int j = startCol; j <= endCol; ++j) {
            structure[wallPosition][j] = 'x';
        }
        int availableCols = (endCol - startCol + 1) / 2;
        if (availableCols <= 0) {
            return;
        }
        int passageCol = startCol + 1 + 2 * (std::rand() % availableCols); // place wall position in a random even column
        if (passageCol < startCol || passageCol > endCol) {
            return;
        }
        structure[wallPosition][passageCol] = '.';

        // calls function again to divide the two sub-areas
        GenerateStructureTest(structure, startRow, wallPosition - 1, startCol, endCol, true);
        GenerateStructureTest(structure, wallPosition + 1, endRow, startCol, endCol, true);
    } else {
        // dividing vertically
        int availableCols = (endCol - startCol) / 2;
        if (availableCols <= 0) {
            return;
        }
        wallPosition = startCol + 1 + 2 * (std::rand() % availableCols); // place wall position in a random even column
        if (wallPosition < startCol || wallPosition > endCol) {
            return;
        }
        for (int i = startRow; i <= endRow; ++i) {
            structure[i][wallPosition] = 'x';
        }
        int availableRows = (endRow - startRow + 1) / 2;
        if (availableRows <= 0) {
            return;
        }
        int passageRow = startRow + 1 + 2 * (std::rand() % availableRows); // place wall position in a random odd row
        if (passageRow < startRow || passageRow > endRow) {
            return;
        }
        structure[passageRow][wallPosition] = '.';
        // calls function again to divide the two sub-areas
        GenerateStructureTest(structure, startRow, endRow, startCol, wallPosition - 1, false);
        GenerateStructureTest(structure, startRow, endRow, wallPosition + 1, endCol, false);
    }
}

void GenerateMazeTest(int rows, int columns) {
    // prints maze structure


    // this seeds the random generator 
    std::srand(std::time(nullptr));

    // initialises vector to store maze structure
    std::vector<std::vector<char>> structure(rows, std::vector<char>(columns, '.'));
    for (int i = 0; i < rows; ++i) {
        structure[i][0] = 'x';
        structure[i][columns - 1] = 'x';
    }
    for (int j = 0; j < columns; ++j) {
        structure[0][j] = 'x';
        structure[rows - 1][j] = 'x';
    }

    // calls function to generate maze structure
    GenerateStructureTest(structure, 1, rows - 2, 1, columns - 2, false);
    // prints maze structure and adds entry/exit 
    structure[0][1] = '.';
    for (const auto& row : structure) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
}
