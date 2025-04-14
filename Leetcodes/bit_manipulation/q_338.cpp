/*
Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.

 

Example 1:

Input: n = 2
Output: [0,1,1]
Explanation:
0 --> 0
1 --> 1
2 --> 10

Example 2:

Input: n = 5
Output: [0,1,1,2,1,2]
Explanation:
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101

 

Constraints:

    0 <= n <= 10^5

*/

class Solution {
private:
    vector<int> by_MSP_iterative_dp(int& n) {
        std::vector<int> dp(n + 1);
        int x = 0;
        int b = 1;

        while (b <= n) {
            while (x < b && x + b <= n) {
                dp[x + b] = dp[x] + 1;
                ++x;
            }

            x = 0;
            b <<= 1;
        }

        return dp;
    }
public:
    vector<int> countBits(int n) {
        return by_MSP_iterative_dp(n);
    }
};