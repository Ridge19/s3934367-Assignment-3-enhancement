#ifndef ENHANCEMENT3_H
#define ENHANCEMENT3_H

#include <vector>
#include "GenerateMaze.h"

class Enhancement3 {
public:
    Enhancement3();  // Constructor
    ~Enhancement3(); // Destructor

    // Function to check for isolated areas and loops in the maze
    void checkForIsolatedAreas(const std::vector<std::vector<int>>& maze);
    void checkForLoops(const std::vector<std::vector<int>>& maze);
};

#endif // ENHANCEMENT3_H