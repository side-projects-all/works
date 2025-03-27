/*
Given an integer rowIndex, return the rowIndexth (0-indexed) row of the Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:

 

Example 1:

Input: rowIndex = 3
Output: [1,3,3,1]

Example 2:

Input: rowIndex = 0
Output: [1]

Example 3:

Input: rowIndex = 1
Output: [1,1]

 

Constraints:

    0 <= rowIndex <= 33

*/

class Solution {
private:
    vector<int> by_iterative_dp(int& rowIndex) {
        if (rowIndex == 0) {
            return {1};
        }

        std::vector<int> dp(rowIndex + 1, 1);

        for (int r = 2; r <= rowIndex; ++r) {
            
            int prev_left_top = dp[0];
            int prev_top = dp[1];
            for (int c = 1; c < r; ++c) {
                
                dp[c] = prev_left_top + prev_top;
                prev_left_top = prev_top;
                prev_top = dp[c + 1];
            }
        }
        
        return dp;
    }
public:
    vector<int> getRow(int rowIndex) {
        return by_iterative_dp(rowIndex);
    }
};