/*
There is a robot on an m x n grid. The robot is initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.

Given the two integers m and n, return the number of possible unique paths that the robot can take to reach the bottom-right corner.

The test cases are generated so that the answer will be less than or equal to 2 * 10^9

Example 1:

Input: m = 3, n = 7
Output: 28

Example 2:

Input: m = 3, n = 2
Output: 3
Explanation: From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down

Constraints:

    1 <= m, n <= 100

*/

class Solution {
private:
    int iterative(int m, int n) {
        //this is just like the 2d climb stair
        std::vector<std::vector<int>> table(m, std::vector<int>(n, 1));

        for (int r = 1; r < m; ++r) {
            for (int c = 1; c < n; ++c) {
                table[r][c] = table[r - 1][c] + table[r][c - 1];
            }
        }

        return table[m - 1][n - 1];
    }

    int recursive(int m, int n, int row, int col, std::vector<std::vector<int>>& mem) {
        if (row >= m || col >= n) {
            return 0;
        }

        if (row == m - 1 && col == n - 1) {
            return 1;
        }

        if (mem[row][col] != -1) {
            return mem[row][col];
        }

        int result = recursive(m, n, row + 1, col, mem) + recursive(m, n, row, col + 1, mem);
        mem[row][col] = result;

        return result;
    }

public:
    int uniquePaths(int m, int n) {
        //std::vector<std::vector<int>> mem(m, std::vector<int>(n, -1));

        //return recursive(m, n, 0, 0, mem);
        return iterative(m, n);
    }
};