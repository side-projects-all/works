/*
Given an integer n, return the count of all numbers with unique digits, x, where 0 <= x < 10n.

 

Example 1:

Input: n = 2
Output: 91
Explanation: The answer should be the total numbers in the range of 0 ≤ x < 100, excluding 11,22,33,44,55,66,77,88,99

Example 2:

Input: n = 0
Output: 1

 

Constraints:

    0 <= n <= 8


*/

class Solution {
private:
    int by_iterative_dp(int& n) {
        if (n == 0) {
            return 1;
        }

        if (n == 1) {
            return 10;
        }

        std::vector<int> dp(n + 1);
        dp[0] = 1;
        dp[1] = 10;

        int digits_left = 9;
        int unique = 9; //the leftmost digit for the length
        for (int len = 2; len <= n; ++len) {
            unique *= digits_left;
            dp[len] = unique + dp[len - 1];
            
            --digits_left;
        }
        return dp[n];
    }
public:
    int countNumbersWithUniqueDigits(int n) {
        return by_iterative_dp(n);
    }
};