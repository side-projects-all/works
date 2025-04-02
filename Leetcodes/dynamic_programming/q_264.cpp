/*
An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.

Given an integer n, return the nth ugly number.

 

Example 1:

Input: n = 10
Output: 12
Explanation: [1, 2, 3, 4, 5, 6, 8, 9, 10, 12] is the sequence of the first 10 ugly numbers.

Example 2:

Input: n = 1
Output: 1
Explanation: 1 has no prime factors, therefore all of its prime factors are limited to 2, 3, and 5.

 

Constraints:

    1 <= n <= 1690


*/

class Solution {
private:
    int by_iterative_dp(int& n) {
        if (n <= 5) {
            return n;
        }

        std::vector<int> dp(n);     //the ith small
        dp[0] = 1;
        int t2 = 0;     //times of 2
        int t3 = 0;     //times of 3
        int t5 = 0;     //times of 5

        for (int i = 1; i < n; ++i) {
            int min_val = std::min({dp[t2] * 2, dp[t3] * 3, dp[t5] * 5});

            if (min_val == dp[t2] * 2) {
                ++t2;
            }
            if (min_val == dp[t3] * 3) {
                ++t3;
            } 
            if (min_val == dp[t5] * 5) {
                ++t5;
            }

            dp[i] = min_val;
        }

        return dp[n - 1]; 
    }
public:
    int nthUglyNumber(int n) {
        return by_iterative_dp(n);
    }
};

