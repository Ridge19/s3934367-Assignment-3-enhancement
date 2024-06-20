#include "Enhancement3.h"
#include <iostream>
#include <vector>
#include <stack>

void Enhancement3::checkForIsolatedAreas(const std::vector<std::vector<int>>& maze) {
    int rows = maze.size();
    if (rows == 0) return;
    int cols = maze[0].size();
    
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    
    // Lambda function to perform DFS
    auto isInsideMaze = [&](int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    };

    auto dfs = [&](int startX, int startY) {
        std::stack<std::pair<int, int>> stack;
        stack.push({startX, startY});
        visited[startX][startY] = true;
        
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while (!stack.empty()) {
            auto [x, y] = stack.top();
            stack.pop();
            
            for (auto& dir : directions) {
                int newX = x + dir[0];
                int newY = y + dir[1];
                
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
    
    std::cout << "Number of isolated areas: " << isolatedAreas << std::endl;
}
