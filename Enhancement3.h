#ifndef ENHANCEMENT3_H
#define ENHANCEMENT3_H

#include <vector>
#include "GenerateMaze.h"

class Enhancement3 {
public:
    Enhancement3();  // Constructor
    ~Enhancement3(); // Destructor
    void checkForIsolatedAreas(const std::vector<std::vector<int>>& maze);
};

#endif // ENHANCEMENT3_H