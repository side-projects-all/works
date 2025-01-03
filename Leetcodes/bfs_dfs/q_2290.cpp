/*
You are given a 0-indexed 2D integer array grid of size m x n. Each cell has one of two values:

    0 represents an empty cell,
    1 represents an obstacle that may be removed.

You can move up, down, left, or right from and to an empty cell.

Return the minimum number of obstacles to remove so you can move from the upper left corner (0, 0) to the lower right corner (m - 1, n - 1).

 

Example 1:

Input: grid = [[0,1,1],[1,1,0],[1,1,0]]
Output: 2
Explanation: We can remove the obstacles at (0, 1) and (0, 2) to create a path from (0, 0) to (2, 2).
It can be shown that we need to remove at least 2 obstacles, so we return 2.
Note that there may be other ways to remove 2 obstacles to create a path.

Example 2:

Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]]
Output: 0
Explanation: We can move from (0, 0) to (2, 4) without removing any obstacles, so we return 0.

 

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 10^5
    2 <= m * n <= 10^5
    grid[i][j] is either 0 or 1.
    grid[0][0] == grid[m - 1][n - 1] == 0


*/

class Solution {
private:
    // Directions for movement: right, left, down, up
    std::vector<std::vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        // Distance matrix to store the minimum obstacles removed to reach each
        // cell
        std::vector<std::vector<int>> minObstacles(m, std::vector<int>(n, INT_MAX));

        minObstacles[0][0] = 0;

        std::deque<std::array<int, 3>> deque;
        deque.push_back({0, 0, 0});  // {obstacles, row, col}

        while (!deque.empty()) {
            auto [obstacles, row, col] = deque.front();
            deque.pop_front();
            

            // Explore all four possible directions from the current cell
            for (auto& dir : directions) {
                int newRow = row + dir[0], newCol = col + dir[1];

                if (isValid(grid, newRow, newCol) &&
                    minObstacles[newRow][newCol] == INT_MAX) {
                    if (grid[newRow][newCol] == 1) {
                        // If it's an obstacle, add 1 to obstacles and push to
                        // the back
                        minObstacles[newRow][newCol] = obstacles + 1;
                        deque.push_back({obstacles + 1, newRow, newCol});
                    } else {
                        // If it's an empty cell, keep the obstacle count and
                        // push to the front
                        minObstacles[newRow][newCol] = obstacles;
                        deque.push_front({obstacles, newRow, newCol});
                    }
                }
            }
        }

        return minObstacles[m - 1][n - 1];
    }

private:
    // Helper method to check if the cell is within the grid bounds
    bool isValid(std::vector<std::vector<int>>& grid, int row, int col) {
        return row >= 0 && col >= 0 && row < grid.size() &&
               col < grid[0].size();
    }
};