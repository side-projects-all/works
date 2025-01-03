/*
Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.

A falling path starts at any element in the first row and chooses the element in the next row that is either directly below or diagonally left/right. Specifically, the next element from position (row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).

Example 1:

Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
Output: 13
Explanation: There are two falling paths with a minimum sum as shown.

Example 2:

Input: matrix = [[-19,57],[-40,-5]]
Output: -59
Explanation: The falling path with a minimum sum is shown.

 
Constraints:

    n == matrix.length == matrix[i].length
    1 <= n <= 100
    -100 <= matrix[i][j] <= 100



*/

class Solution {
private:
    int iterative(vector<vector<int>>& matrix) {
        /*
        int rows = matrix.size();
        int cols = matrix[0].size();

        std::vector<std::vector<int>> dp(rows, std::vector<int>(cols, 0));
        dp[0] = matrix[0];

        for (int r = 1; r < rows; ++r) {

            for (int c = 0; c < cols; ++c) {
                int left_i = std::max(0, -1 + c);
                int right_i = std::min(cols - 1, c + 1);

                dp[r][c] = matrix[r][c] + std::min(dp[r - 1][c], 
                                            std::min(dp[r - 1][left_i], dp[r - 1][right_i]));
            }
        }

        int min_val = *std::min_element(dp[rows - 1].begin(), dp[rows - 1].end());

        return min_val;
        */
        int rows = matrix.size();
        int cols = matrix[0].size();

        if (rows == 1) {
            return *std::min_element(matrix[0].begin(), matrix[0].end());
        }

        std::vector<std::vector<int>> dp(2, std::vector<int>(cols));
        dp[0] = matrix[0];

        for (int r = 1; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                dp[1][c] = matrix[r][c];

                int prev_left = INT_MAX;
                int prev = dp[0][c];
                int prev_right = INT_MAX;

                if (c - 1 >= 0) {
                    prev_left = dp[0][c - 1];
                }

                if (c + 1 < cols) {
                    prev_right = dp[0][c + 1];
                }

                dp[1][c] += std::min({prev_left, prev, prev_right});
            }

            dp[0] = dp[1];
        }

        return *std::min_element(dp[1].begin(), dp[1].end());;
    }

    int recursive(vector<vector<int>>& matrix, int r, int c, std::vector<std::vector<int>>& mem, int bigNum) {
        //base case 
        if (r < 0) {
            return 0;
        }

        //for column is out of range
        if (c < 0 || c >= matrix[0].size()) {
            return bigNum;
        }

        if (mem[r][c] != 10001) {
            return mem[r][c];
        }

        int left = recursive(matrix, r - 1, c - 1, mem, bigNum);
        int up = recursive(matrix, r - 1, c, mem, bigNum);
        int right = recursive(matrix, r - 1, c + 1, mem, bigNum);

        mem[r][c] = matrix[r][c] + std::min(left, std::min(up, right));
        
        return mem[r][c];
    }

public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        /*
        int rows = matrix.size();
        int cols = matrix[0].size();

        int bigNum = 10001;
        std::vector<std::vector<int>> mem(rows, std::vector<int>(cols, 10001));
        int min = 10001;
        
        //the point is the minimum of accumulation
        for (int c = 0; c < cols; ++c) {
            min = std::min(min, recursive(matrix, rows - 1, c, mem, bigNum));
        }
        
        return min;
        */

        return iterative(matrix);
    }
};