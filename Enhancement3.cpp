#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

class Maze {
public:
    Maze(const vector<string>& maze) : maze(maze), n(maze.size()), m(maze[0].size()) {
        visited.resize(n, vector<bool>(m, false));
    }

    bool hasIsolatedAreas() {
        // Initialize flood fill to find connected areas
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (maze[i][j] == '.' && !visited[i][j]) {
                    if (hasUnvisitedArea(i, j)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool hasLoops() {
        // Reset visited for loop detection
        fill(visited.begin(), visited.end(), vector<bool>(m, false));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (maze[i][j] == '.' && !visited[i][j]) {
                    if (dfs(i, j, -1, -1)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

private:
    vector<string> maze;
    vector<vector<bool>> visited;
    int n, m;

    bool hasUnvisitedArea(int x, int y) {
        queue<pair<int, int>> q;
        q.push({x, y});
        visited[x][y] = true;
        bool foundUnvisited = false;

        while (!q.empty()) {
            auto [cx, cy] = q.front();
            q.pop();

            for (int dir = 0; dir < 4; ++dir) {
                int nx = cx + dx[dir];
                int ny = cy + dy[dir];

                if (isInBounds(nx, ny) && maze[nx][ny] == '.' && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }

        // Check if there's any unvisited open space
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (maze[i][j] == '.' && !visited[i][j]) {
                    foundUnvisited = true;
                }
            }
        }

        return foundUnvisited;
    }

    bool dfs(int x, int y, int px, int py) {
        visited[x][y] = true;

        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (isInBounds(nx, ny) && maze[nx][ny] == '.') {
                if (!visited[nx][ny]) {
                    if (dfs(nx, ny, x, y)) {
                        return true;
                    }
                } else if (nx != px || ny != py) {
                    return true;
                }
            }
        }

        return false;
    }

    bool isInBounds(int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    }
};

int main() {
    vector<string> maze = {
        "xxxxx",
        "x...x",
        "xx.xx",
        "x...x",
        "xxxxx"
    };

    Maze m(maze);

    if (m.hasIsolatedAreas()) {
        cout << "The maze has isolated areas." << endl;
    } else {
        cout << "The maze does not have isolated areas." << endl;
    }

    if (m.hasLoops()) {
        cout << "The maze has loops." << endl;
    } else {
        cout << "The maze does not have loops." << endl;
    }

    return 0;
}