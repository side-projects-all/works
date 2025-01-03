/*
you are given an m x n integer array grid. There is a robot initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m-1][n-1]). The robot can only move either down or right at any point in time.

An obstacle and space are marked as 1 or 0 respectively in grid. A path that the robot takes cannot include any square that is an obstacle.

Return the number of possible unique paths that the robot can take to reach the bottom-right corner.

The testcases are generated so that the answer will be less than or equal to 2 * 10^9.

Example 1:

Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Explanation: There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right

Example 2:

Input: obstacleGrid = [[0,1],[0,0]]
Output: 1

Constraints:

    m == obstacleGrid.length
    n == obstacleGrid[i].length
    1 <= m, n <= 100
    obstacleGrid[i][j] is 0 or 1.

*/

class Solution {
private:
    int iterative(vector<vector<int>>& obstacleGrid) {
        /*
        int rows = obstacleGrid.size();
        int cols = obstacleGrid[0].size();

        std::vector<std::vector<int>> mem(rows, std::vector<int>(cols, 0));

        if (obstacleGrid[0][0] != 1) {
            mem[0][0] = 1;
        }
        
        for (int r = 1; r < rows; ++r) {
            if (obstacleGrid[r][0] != 1) {
                mem[r][0] += mem[r - 1][0];
            } else {
                mem[r][0] = 0;
            }
        }

        for (int c = 1; c < cols; ++c) {
            if (obstacleGrid[0][c] != 1) {
                mem[0][c] += mem[0][c - 1];
            } else {
                mem[0][c] = 0;
            }
        }

        for (int r = 1; r < rows; ++r) {
            for (int c = 1; c < cols; ++c) {

                if (obstacleGrid[r][c] != 1) {
                    mem[r][c] = mem[r - 1][c] + mem[r][c - 1];
                } else {
                    mem[r][c] = 0;
                }
                
            }
        }


        return mem[rows - 1][cols - 1];
        */
        
        int rows = obstacleGrid.size();
        int cols = obstacleGrid[0].size();

        if (obstacleGrid[0][0] == 1 || obstacleGrid[rows - 1][cols - 1] == 1) {
            return 0;
        }
        std::vector<std::vector<int>> dp(rows, std::vector<int>(cols, 0));
        dp[0][0] = 1;

        for (int c = 1; c < cols; ++c) {
            if (obstacleGrid[0][c] != 1) {
                dp[0][c] = 1;
            } else {
                break;
            }
        }

        for (int r = 1; r < rows; ++r) {
            if (obstacleGrid[r][0] != 1) {
                dp[r][0] = 1;
            } else {
                break;
            }
        }
        for (int r = 1; r < rows; ++r) {
            for (int c = 1; c < cols; ++c) {

                if (obstacleGrid[r][c] == 1) {
                    dp[r][c] = 0;
                    continue;
                }

                dp[r][c] = dp[r - 1][c] + dp[r][c - 1];
            }
        }

        return dp[rows - 1][cols - 1];
    }

    int recursive(vector<vector<int>>& obstacleGrid, int r, int c, std::vector<std::vector<int>>& mem) {
        if (r < 0 || c < 0) {
            return 0;
        }

        if (r == 0 && c == 0 && obstacleGrid[r][c] != 1) {
            return 1;
        }

        if (obstacleGrid[r][c] == 1) {
            return 0;
        }

        if (mem[r][c] != -1) {
            return mem[r][c];
        }

        mem[r][c] = recursive(obstacleGrid, r - 1, c, mem) + recursive(obstacleGrid, r, c - 1, mem);

        return mem[r][c];
    }

public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        //int rows = obstacleGrid.size();
        //int cols = obstacleGrid[0].size();

        //std::vector<std::vector<int>> mem(rows, std::vector<int>(cols, -1));

        //return recursive(obstacleGrid, rows - 1, cols - 1, mem);
        return iterative(obstacleGrid);
    }
};