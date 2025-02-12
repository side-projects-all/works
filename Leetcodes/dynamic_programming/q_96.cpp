/*
Given an integer n, return the number of structurally unique BST's (binary search trees) which has exactly n nodes of unique values from 1 to n.

 

Example 1:

Input: n = 3
Output: 5

Example 2:

Input: n = 1
Output: 1

 

Constraints:

    1 <= n <= 19


*/

class Solution {
private:
    int byCatalanNumber(int n) {
        long c = 1;
        for (int i = 0; i < n; ++i) {
            c = c * 2 * (2 * i + 1) / (i + 2);
        }

        return c;
    }

    int iterative(int n) {
        if (n == 1) {
            return 1;
        }

        std::vector<int> dp(n + 1);
        dp[0] = 1;
        dp[1] = 1;

        for (int nodes = 2; nodes <= n; ++nodes) {
            for (int left = 0; left < nodes; ++left) {
                dp[nodes] += dp[left] * dp[nodes - left - 1];
            }

            /* two ways to complete, 1 index diff
            for (int left = 1; left <= nodes; ++left) {
                dp[nodes] += dp[left - 1] * dp[nodes - left];
            }
            */
        }

        return dp[n];
    }
public:
    int numTrees(int n) {
        //return iterative(n);
        return byCatalanNumber(n);
    }
};