/*
Given an m x n integers matrix, return the length of the longest increasing path in matrix.

From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).

 

Example 1:

Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
Output: 4
Explanation: The longest increasing path is [1, 2, 6, 9].

Example 2:

Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
Output: 4
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.

Example 3:

Input: matrix = [[1]]
Output: 1

 

Constraints:

    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 200
    0 <= matrix[i][j] <= 2^31 - 1


*/

class Solution {
private:
    int recursive(vector<vector<int>>& matrix, int& rows, int& cols, std::vector<std::vector<int>>& mem, int (&dirs)[4][2], int r, int c) {
        if (mem[r][c] != -1) {
            return mem[r][c];
        }

        int len = 1;
        for (int i = 0; i < 4; ++i) {
            int nr = dirs[i][0] + r;
            int nc = dirs[i][1] + c;

            if (nr < 0 || nr == rows || nc < 0 || nc == cols || matrix[nr][nc] <= matrix[r][c]) {
                continue;
            }

            len = std::max(len, 1 + recursive(matrix, rows, cols, mem, dirs, nr, nc));
        }

        return mem[r][c] = len;
    }
    int by_recursive_dp(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        std::vector<std::vector<int>> mem(rows, std::vector<int>(cols, -1));
        int dirs[4][2]{ {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

        int max_len = 0;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                max_len = std::max(max_len, recursive(matrix, rows, cols, mem, dirs, r, c));
            }
        }

        return max_len;
    }
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        return by_recursive_dp(matrix);
    }
};