/*
Given an integer numRows, return the first numRows of Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:


Example 1:

Input: numRows = 5
Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]

Example 2:

Input: numRows = 1
Output: [[1]]

 
Constraints:

    1 <= numRows <= 30

*/

class Solution {
private:
    vector<vector<int>> by_iterative_dp(int& numRows) {
        if (numRows == 1) {
            return {{1}};
        }

        std::vector<std::vector<int>> dp(numRows);
        dp[0] = {1};
        dp[1] = {1, 1};

        for (int r = 2; r < numRows; ++r) {
            dp[r] = std::vector<int>(r + 1);
            dp[r][0] = 1;
            dp[r][r] = 1;

            for (int c = 1; c < r; ++c) {
                dp[r][c] = dp[r - 1][c - 1] + dp[r - 1][c];
            }
        }

        return dp;
    }
public:
    vector<vector<int>> generate(int numRows) {
        return by_iterative_dp(numRows);
    }
};