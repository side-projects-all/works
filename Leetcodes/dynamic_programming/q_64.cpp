/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example 1:

Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
Output: 7
Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.

Example 2:

Input: grid = [[1,2,3],[4,5,6]]
Output: 12

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 200
    0 <= grid[i][j] <= 100

*/

class Solution {
private:
    int iterative(std::vector<std::vector<int>>& grid) {
        /*
        int rows = grid.size();
        int cols = grid[0].size();

        std::vector<std::vector<int>> mem(rows, std::vector<int>(cols, -1));
        mem[0][0] = grid[0][0];

        for (int r = 1; r < rows; ++r) {
            mem[r][0] = grid[r][0] + mem[r - 1][0];
        }

        for (int c = 1; c < cols; ++c) {
            mem[0][c] = grid[0][c] + mem[0][c - 1];
        }

        for (int r = 1; r < rows; ++r) {
            for (int c = 1; c < cols; ++c) {
                mem[r][c] =  grid[r][c] + std::min(mem[r - 1][c], mem[r][c - 1]);
            }
        }

        return mem[rows - 1][cols - 1];
        */
        
        int rows = grid.size();
        int cols = grid[0].size();

        if (rows == 1 && cols == 1) {
            return grid[0][0];
        }

        std::vector<std::vector<int>> dp(rows, std::vector<int>(cols, 0));
        dp[0][0] = grid[0][0];

        for (int r = 1; r < rows; ++r) {
            dp[r][0] = dp[r - 1][0] + grid[r][0];
        }

        for (int c = 1; c < cols; ++c) {
            dp[0][c] = dp[0][c - 1] + grid[0][c];
        }

        for (int r = 1; r < rows; ++r) {
            for (int c = 1; c < cols; ++c) {
                dp[r][c] = grid[r][c] + std::min(dp[r - 1][c], dp[r][c - 1]);
            }
        }

        return dp[rows - 1][cols - 1];
    }

    int recursive(std::vector<std::vector<int>>& grid, int r, int c, std::vector<std::vector<int>>& mem) {
        if (r < 0 || c < 0) {
            return 201;
        }

        if (r == 0 && c == 0) {
            return grid[r][c];
        }

        if (mem[r][c] != -1) {
            return mem[r][c];
        }

        mem[r][c] = grid[r][c] + std::min(recursive(grid, r - 1, c, mem), recursive(grid, r, c - 1, mem));

        return mem[r][c];
    }

public:
    int minPathSum(vector<vector<int>>& grid) {
        //int r = grid.size() - 1;
        //int c = grid[0].size() - 1;

        //std::vector<std::vector<int>> mem(r, std::vector<int>(c, -1));

        //return recursive(grid, r, c, mem);
        return iterative(grid);
    }
};