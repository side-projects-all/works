/*
Given a triangle array, return the minimum path sum from top to bottom.

For each step, you may move to an adjacent number of the row below. More formally, if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.

 

Example 1:

Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).

Example 2:

Input: triangle = [[-10]]
Output: -10

 

Constraints:

    1 <= triangle.length <= 200
    triangle[0].length == 1
    triangle[i].length == triangle[i - 1].length + 1
    -104 <= triangle[i][j] <= 104

 
Follow up: Could you do this using only O(n) extra space, where n is the total number of rows in the triangle?
*/

class Solution {
private:
    int iterative(vector<vector<int>>& triangle) {
        /*
        int rows = triangle.size();
        int cols = triangle[rows - 1].size();
        int bigNum = 10001 * cols;

        std::vector<std::vector<int>> mem(cols, std::vector<int>(cols));
        mem[0][0] = triangle[0][0];
        

        for (int r = 1; r < triangle.size(); ++r) {

            for (int c = 0; c < triangle[r].size(); ++c) {
                int prev = 0;
                int prevMinusOne = 0;

                if (c < 0 || c >= triangle[r - 1].size()) {
                    prev = bigNum;
                } else {
                    //prev = triangle[r - 1][c];
                    prev = mem[r - 1][c];
                }

                if (c - 1 < 0 || c - 1 >= triangle[r - 1].size()) {
                    prevMinusOne = bigNum;
                } else {
                    //prevMinusOne = triangle[r - 1][c - 1];
                    prevMinusOne = mem[r - 1][c - 1];
                }

                mem[r][c] = triangle[r][c] + std::min(prev, prevMinusOne);
                
            }
        }
        int min = bigNum;

        for (int i = 0; i < cols; ++i) {
            min = std::min(min, mem[rows - 1][i]);
        }
        
        return min;
        */
        
        int rows = triangle.size();
        int cols = triangle[rows - 1].size();

        if (rows == 1) {
            return triangle[0][0];
        }

        std::vector<std::vector<int>> dp(2, std::vector<int>(cols));
        dp[0][0] = triangle[0][0];

        for (int r = 1; r < rows; ++r) {

            int prev_rows = r - 1;
            int prev_cols = triangle[r - 1].size();

            int curr_cols = triangle[r].size();

            dp[1][0] = dp[0][0] + triangle[r][0];
            dp[1][curr_cols - 1] = dp[0][prev_cols - 1] + triangle[r][curr_cols - 1];

            for (int c = 1; c < curr_cols - 1; ++c) {
                dp[1][c] = triangle[r][c] + std::min(dp[0][c], dp[0][c - 1]);
            }

            dp[0] = dp[1];
        }

        int min = INT_MAX;
        for (int c = 0; c < cols; ++c) {
            min = std::min(min, dp[1][c]);
        }

        return min;
    }

    int recursive(vector<vector<int>>& triangle, int r, int c, std::vector<std::vector<int>>& mem, const int& bigNum) {
        
        if (c < 0 || c >= triangle[r].size()) {
            return bigNum;    //give a limitation for comparison
        }

        if (r == 0 && c == 0) {
            return triangle[0][0];
        }

        //if it was not a limitation, we retrieve val from mem
        if (mem[r][c] != bigNum) {
            return mem[r][c];
        }

        mem[r][c] = triangle[r][c] + std::min(recursive(triangle, r - 1, c - 1, mem, bigNum), 
                                                recursive(triangle, r - 1, c, mem, bigNum));

        return mem[r][c];
    }

public:
    int minimumTotal(vector<vector<int>>& triangle) {
        /*
        int rows = triangle.size();
        int cols = triangle[rows - 1].size();
        int bigNum = 10001 * cols;
        int min = bigNum;

        std::vector<std::vector<int>> mem(cols, std::vector<int>(cols, bigNum));
        

        for (int i = 0; i < cols; ++i) {
            min = std::min(min, recursive(triangle, rows - 1, i, mem, bigNum));
        }
        
        return min;
        */

        return iterative(triangle);
    }
};