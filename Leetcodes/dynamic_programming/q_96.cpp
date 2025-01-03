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
        std::vector<int> mem(n + 1);
        mem[0] = 1;
        mem[1] = 1;

        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                mem[i] += mem[j - 1] * mem[i - j];
            }
        }

        return mem[n];
    }
public:
    int numTrees(int n) {
        //return iterative(n);
        return byCatalanNumber(n);
    }
};