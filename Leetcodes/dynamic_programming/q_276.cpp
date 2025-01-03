/*
You are painting a fence of n posts with k different colors. You must paint the posts following these rules:

    Every post must be painted exactly one color.
    There cannot be three or more consecutive posts with the same color.

Given the two integers n and k, return the number of ways you can paint the fence.

ex1:
Input: n = 3, k = 2
Output: 6
Explanation: All the possibilities are shown.
Note that painting all the posts red or all the posts green is invalid because there cannot be three posts in a row with the same color.

ex2:
Input: n = 1, k = 1
Output: 1

ex3:
Input: n = 7, k = 2
Output: 42

Constraints:

    1 <= n <= 50
    1 <= k <= 105
    The testcases are generated such that the answer is in the range [0, 231 - 1] for the given n and k.


*/

class Solution {
private:
    int iterative(int n, int k) {
        if (n == 1) {
            return k;
        }

        if (n == 2) {
            return k * k;
        }

        std::vector<int> mem(n + 1, 0);
        mem[1] = k;
        mem[2] = k * k;

        for (int i = 3; i <= n; ++i) {
            mem[i] = (k - 1) * (mem[i - 1] + mem[i - 2]);
        }

        return mem[n];
    }
    int recursive(int n, int k, std::vector<int>& mem) {
        if (n == 1) {
            return k;
        }

        if (n == 2) {
            return k * k;
        }

        if (mem[n] != -1) {
            return mem[n];
        }

        //mem[n] = (k - 1) * recursive(n - 1, k, mem) + 1 * (k - 1) * recursive(n - 2, k, mem);
        mem[n] = (k - 1) * (recursive(n - 1, k, mem) + recursive(n - 2, k, mem));

        return mem[n];
    }
public:
    int numWays(int n, int k) {
        //std::vector<int> mem(n + 1, -1);

        //return recursive(n, k, mem);
        return iterative(n, k);
    }
};