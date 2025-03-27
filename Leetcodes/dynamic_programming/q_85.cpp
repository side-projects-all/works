/*
Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

 

Example 1:

Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.

Example 2:

Input: matrix = [["0"]]
Output: 0

Example 3:

Input: matrix = [["1"]]
Output: 1

 

Constraints:

    rows == matrix.length
    cols == matrix[i].length
    1 <= row, cols <= 200
    matrix[i][j] is '0' or '1'.


*/

class Solution {
private:
    int by_better_iterative_dp(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        int max_area = 0;
        std::vector<int> left(cols);
        std::vector<int> right(cols, cols);
        std::vector<int> height(cols);

        for (int r = 0; r < rows; ++r) {

            int curr_left = 0;
            int curr_right = cols;
            for (int c = 0; c < cols; ++c) {

                if (matrix[r][c] == '1') {
                    ++height[c];
                    left[c] = std::max(left[c], curr_left);

                } else {
                    height[c] = 0;
                    left[c] = 0;
                    curr_left = c + 1;
                }

                /*
                if (matrix[r][cols - c - 1] == '1') {
                    right[cols - c - 1] = std::min(right[cols - c - 1], curr_right);

                } else {
                    right[cols - c - 1] = cols;
                    curr_right = cols - c - 1;
                }
                */
            }
            
            //for easier understanding
            for (int c = cols - 1; c >= 0; --c) {
                if (matrix[r][c] == '1') {
                    right[c] = std::min(right[c], curr_right);

                } else {
                    right[c] = cols;
                    curr_right = c;
                }
            }

            for (int c = 0; c < cols; ++c) {
                max_area = std::max(max_area, (right[c] - left[c]) * height[c]);
            }
        }

        return max_area;
    }
    int by_stack(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        int max_area = 0;

        //combine the dp and stack by the histogram idea
        std::vector<int> dp(cols);        //height at every column
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                dp[c] = matrix[r][c] == '1' ? dp[c] + 1 : 0;
            }

            int area = 0;
            std::vector<int> stack = { -1 };
            for (int i = 0; i < cols; ++i) {
                while (stack.back() != -1 && dp[stack.back()] >= dp[i]) {
                    int h = dp[stack.back()];
                    stack.pop_back();
                    area = std::max(area, h * (i - stack.back() - 1));
                }

                stack.push_back(i);
            }

            while (stack.back() != -1) {
                int h = dp[stack.back()];
                stack.pop_back();
                area = std::max(area, h * (cols - stack.back() - 1));    
            }

            max_area = std::max(max_area, area);
        }

        return max_area;
    }
    int by_iterative_dp(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        std::vector<std::vector<int>> dp(rows, std::vector<int>(cols));
        int max_area = 0;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (matrix[r][c] == '1') {
                    dp[r][c] = c == 0 ? 1 : dp[r][c - 1] + 1;

                    int w = dp[r][c];
                    for (int top = r; top >= 0; --top) {
                        int h = r - top + 1;
                        w = std::min(w, dp[top][c]);
                        max_area = std::max(max_area, w * h);
                    }
                }
            }
        }

        return max_area;
    }
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        //return by_iterative_dp(matrix);
        
        //return by_stack(matrix);
        
        return by_better_iterative_dp(matrix);
    }
};