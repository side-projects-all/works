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
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        rows = matrix.size();
        cols = matrix[0].size();
        //return by_topological_sort(matrix);
        return by_dfs(matrix);
    }

private:
    const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int rows;
    int cols;

    int by_dfs(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        std::vector<std::vector<int>> mem(rows, std::vector<int>(cols, -1));
        int ans = 0;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                ans = std::max(ans, dfs(matrix, r, c, mem));
            }
        }

        return ans;
    }

    int dfs(vector<vector<int>>& matrix, int r, int c, vector<vector<int>>& mem) {

        if (mem[r][c] != -1) {
            return mem[r][c];
        }

        int take = 1;
        for (auto d : dirs) {
            int next_r = r + d[0];
            int next_c = c + d[1];

            if (next_r >= 0 && next_r < rows && 
                next_c >= 0 && next_c < cols && 
                matrix[next_r][next_c] > matrix[r][c]) {
                
                take = std::max(take, 1 + dfs(matrix, next_r, next_c, mem));
            }
        }

        return mem[r][c] = take;
    }

    int by_topological_sort(vector<vector<int>>& matrix) {
        std::vector<std::vector<int>> indegrees(rows, std::vector<int>(cols));
        std::queue<std::pair<int, int>> q;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                for (auto d : dirs) {
                    int prev_r = r + d[0];
                    int prev_c = c + d[1];

                    if (prev_r >= 0 && prev_r < rows && prev_c >= 0 && prev_c < cols) {

                        if (matrix[prev_r][prev_c] < matrix[r][c]) {
                            ++indegrees[r][c];
                        }
                    }
                }

                if (!indegrees[r][c]) {
                    q.push({r, c});
                }
            }
        }

        int ans = 0;
        while (!q.empty()) {
            int len = q.size();

            while (len--) {
                auto [r, c] = q.front();
                q.pop();

                for (auto d : dirs) {
                    int next_r = r + d[0];
                    int next_c = c + d[1];

                    if (next_r >= 0 && next_r < rows && next_c >= 0 && next_c < cols) {

                        if (matrix[r][c] < matrix[next_r][next_c] && 
                                        --indegrees[next_r][next_c] == 0) {
                                            
                            q.push({next_r, next_c});
                        }
                    }
                }
            }

            ++ans;
        }

        return ans;
    }
};