#include "Enhancement3.h"
#include <iostream>
#include <vector>
#include <stack>

// Constructor
Enhancement3::Enhancement3() {
}

// Destructor
Enhancement3::~Enhancement3() {
}

// Function to check for isolated areas in the maze
void Enhancement3::checkForIsolatedAreas(const std::vector<std::vector<int>>& maze) {
    // Check if the maze is empty
    int rows = maze.size();
    if (rows == 0) return;
    int cols = maze[0].size();
    
    // Initialize a 2D vector to keep track of visited cells
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    
    // Lambda function to perform DFS
    auto isInsideMaze = [&](int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    };

    // Lambda function to perform DFS
    auto dfs = [&](int startX, int startY) {
        std::stack<std::pair<int, int>> stack;
        stack.push({startX, startY});
        visited[startX][startY] = true;
        
        // Directions: Up, Down, Left, Right
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        // Perform DFS
        while (!stack.empty()) {
            // Get the top element from the stack
            auto [x, y] = stack.top();
            stack.pop();

            // Check all four directions
            for (auto& dir : directions) {
                int newX = x + dir[0];
                int newY = y + dir[1];
                
                // If the new cell is inside the maze, is a path cell, and has not been visited yet
                if (isInsideMaze(newX, newY) && maze[newX][newY] == 1 && !visited[newX][newY]) {
                    visited[newX][newY] = true;
                    stack.push({newX, newY});
                }
            }
        }
    };
    
    // Check for isolated areas by running DFS from each unvisited path cell
    int isolatedAreas = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] == 1 && !visited[i][j]) {
                isolatedAreas++;
                dfs(i, j);
            }
        }
    }
    
    // Output the number of isolated areas
    std::cout << "Number of isolated areas: " << isolatedAreas << "\n" << std::endl;
}

// Function to check for loops in the maze
void Enhancement3::checkForLoops(const std::vector<std::vector<int>>& maze) {
    // Check if the maze is empty
    int rows = maze.size();
    if (rows == 0) return;
    int cols = maze[0].size();
    
    // Initialize a 2D vector to keep track of visited cells
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    bool hasLoop = false; // Variable to check if the maze has loops
    
    // Lambda function to perform DFS
    auto isInsideMaze = [&](int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    };

    // Lambda function to perform DFS and check for cycles
    auto dfs = [&](int startX, int startY) {
        std::stack<std::tuple<int, int, int, int>> stack; // {currentX, currentY, parentX, parentY}
        stack.push({startX, startY, -1, -1});
        visited[startX][startY] = true;
        
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        // Perform DFS
        while (!stack.empty()) {
            // Get the top element from the stack
            auto [x, y, parentX, parentY] = stack.top();
            stack.pop();

            // Check all four directions
            for (auto& dir : directions) {
                int newX = x + dir[0];
                int newY = y + dir[1];
                
                // If the new cell is inside the maze, is a path cell
                if (isInsideMaze(newX, newY) && maze[newX][newY] == 1) {
                    if (!visited[newX][newY]) {
                        visited[newX][newY] = true;
                        stack.push({newX, newY, x, y});
                    } else if (!(newX == parentX && newY == parentY)) {
                        // If the cell is visited and not the parent, we found a loop
                        hasLoop = true;
                    }
                }
            }
        }
    };
    
    // Check for loops by running DFS from each unvisited path cell
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] == 1 && !visited[i][j]) {
                dfs(i, j);
            }
        }
    }
    
    // Output if there are loops
    if (hasLoop) {
        std::cout << "The maze has loops." << "\n" << std::endl;
    } else {
        std::cout << "The maze has no loops." << "\n" << std::endl;
    }
}
