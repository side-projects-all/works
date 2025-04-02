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
    int by_optimize_iterative_dp(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        if (rows == 1 && cols == 1) {
            return matrix[0][0] - '0';
        }

        if (rows == 1) {
            for (int c = 0; c < cols; ++c) {
                if (matrix[0][c] == '1') {
                    return 1;
                }
            }
            return 0;
        }
        if (cols == 1) {
            for (int r = 0; r < rows; ++r) {
                if (matrix[r][0] == '1') {
                    return 1;
                }
            }
            return 0;
        }

        std::vector<int> dp(cols);  //initialize with first row
        int max_len = 0;
        if (matrix[0][0] == '1') {
            dp[0] = 1;
            max_len = 1;
        }
        for (int c = 1; c < cols; ++c) {
            if (matrix[0][c] == '1') {
                dp[c] = 1;
                max_len = 1;
            }
        }

        
        for (int r = 1; r < rows; ++r) {

            int top_left = matrix[r - 1][0] - '0';
            if (top_left == 1) {
                max_len = std::max(max_len, top_left);  //for corner case: '1' only exists on the first column
            }

            dp[0] = matrix[r][0] - '0'; //for init left
            for (int c = 1; c < cols; ++c) {

                int top = dp[c];
                if (matrix[r][c] == '1') {
                    
                    //from left, top, top left
                    dp[c] = 1 + std::min({dp[c - 1], top, top_left});

                    max_len = std::max(max_len, dp[c]);
                    
                } else {
                    dp[c] = 0;
                }

                top_left = top;
            }
        }

        return max_len * max_len;

    }
    int by_iterative_dp(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        if (rows == 1 && cols == 1) {
            return matrix[0][0] - '0';
        }

        if (rows == 1) {
            for (int c = 0; c < cols; ++c) {
                if (matrix[0][c] == '1') {
                    return 1;
                }
            }
            return 0;
        }
        if (cols == 1) {
            for (int r = 0; r < rows; ++r) {
                if (matrix[r][0] == '1') {
                    return 1;
                }
            }
            return 0;
        }

        std::vector<std::vector<int>> dp(rows, std::vector<int>(cols));     //it means max square length
        int max_len = 0;
        if (matrix[0][0] == '1') {
            dp[0][0] = 1;
            max_len = 1;
        }
        for (int c = 1; c < cols; ++c) {
            if (matrix[0][c] == '1') {
                dp[0][c] = 1;
                max_len = 1;
            }
        }
        for (int r = 1; r < rows; ++r) {
            if (matrix[r][0] == '1') {
                dp[r][0] =  1;
                max_len = 1;
            }
        }

        for (int r = 1; r < rows; ++r) {
            for (int c = 1; c < cols; ++c) {
                if (matrix[r][c] == '1') {
                    //from left, top, top left
                    dp[r][c] = 1 + std::min({dp[r][c - 1], dp[r - 1][c], dp[r - 1][c - 1]});

                    max_len = std::max(max_len, dp[r][c]);
                }
            }
        }

        return max_len * max_len;
    }
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        //return by_iterative_dp(matrix);
        
        return by_optimize_iterative_dp(matrix);
    }
};