#ifndef TESTMODE_H
#define TESTMODE_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

class TestMode {
public:
    TestMode();
    TestMode(int rows, int columns); // Constructor to initialize the random number generator
    void GenerateMazeTest(int rows, int columns); // Public method to generate the maze

private:
    void GenerateStructureTest(std::vector<std::vector<char>>& structure, int startRow, int endRow, int startCol, int endCol);

    // Private method to recursively generate the maze structure
};

#endif // TESTMODE_H
