/*
Given an m x n binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

 

Example 1:

Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 4

Example 2:

Input: matrix = [["0","1"],["1","0"]]
Output: 1

Example 3:

Input: matrix = [["0"]]
Output: 0

 

Constraints:

    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 300
    matrix[i][j] is '0' or '1'.


*/

class Solution {
private:
    int iterative(vector<vector<char>>& matrix) {
        /*
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        int max = 0;
        std::vector<std::vector<int>> mem(rows + 1, std::vector<int>(cols + 1, 0));
        
        for (int r = 1; r < rows + 1; ++r) {
            for (int c = 1; c < cols + 1; ++c) {

                if (matrix[r - 1][c - 1] == '1') {
                    mem[r][c] = (std::min(mem[r - 1][c - 1], 
                                    std::min(mem[r - 1][c], mem[r][c - 1]))) + 1;

                    max = std::max(max, mem[r][c]);
                }                
            }
        }

        return max * max;
        */
        
        int rows = matrix.size();
        int cols = matrix[0].size();

        int top_left = 0;
        std::vector<int> dp(cols + 1);
        int max_len = 0;

        for (int r = 1; r < rows + 1; ++r) {
            for (int c = 1; c < cols + 1; ++c) {
                int top = dp[c];

                if (matrix[r - 1][c - 1] == '1') {
                    //top_left: top_left dp position
                    //dp[c - 1]: left dp position
                    //dp[c]: upper dp position
                    dp[c] = std::min({top_left, dp[c - 1], dp[c]}) + 1;
                    max_len = std::max(max_len, dp[c]);
                } else {
                    dp[c] = 0;
                }

                top_left = top;
            }
        }

        return max_len * max_len;
    }

    int recursive(vector<vector<char>>& matrix, int r, int c, std::vector<std::vector<int>>& mem, int& max) {
        if (r == 0 || c == 0) {
            return mem[r][c];
        }

        if (mem[r][c] != -1) {
            return mem[r][c];
        }

        int top = recursive(matrix, r - 1, c, mem, max);
        int left = recursive(matrix, r, c - 1, mem, max);
        int leftTop = recursive(matrix, r - 1, c - 1, mem, max);

        if (matrix[r][c] == '1') {
            mem[r][c] = std::min(top, std::min(left, leftTop)) + 1;
        } else {
            mem[r][c] = 0;
        }

        max = std::max(max, mem[r][c]);

        return mem[r][c];
    }

public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        //edge case
        if (rows == 1 && cols == 1) {
            return (matrix[0][0] == '1') ? 1 : 0;
        }

        /*
        std::vector<std::vector<int>> mem(rows, std::vector<int>(cols, -1));

        int max = -1;
        for (int c = 0; c < cols; ++c) {
            mem[0][c] = matrix[0][c] - '0';
            max = std::max(max, mem[0][c]);
        }

        for (int r = 1; r < rows; ++r) {
            mem[r][0] = matrix[r][0] - '0';
            max = std::max(max, mem[r][0]);
        }

        recursive(matrix, rows - 1, cols - 1, mem, max);

        return max * max;
        */

        return iterative(matrix);
    }
};