/*
Given an integer n, break it into the sum of k positive integers, where k >= 2, and maximize the product of those integers.

Return the maximum product you can get.

 

Example 1:

Input: n = 2
Output: 1
Explanation: 2 = 1 + 1, 1 × 1 = 1.

Example 2:

Input: n = 10
Output: 36
Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.

 

Constraints:

    2 <= n <= 58


*/

class Solution {
private:
    int by_iterative_dp(int& n) {
        if (n <= 3) {
            return n - 1;
        }

        std::vector<int> dp(n + 1);
        //basic setting, can not be avoided!
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 3;

        for (int v = 4; v <= n; ++v) {

            for (int p = 2; p < v; ++p) {
                dp[v]  = std::max(dp[v] , p * dp[v - p]);
            }
        }

        return dp[n];
    }
public:
    int integerBreak(int n) {
        return by_iterative_dp(n);
    }
};