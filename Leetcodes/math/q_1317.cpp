/*
No-Zero integer is a positive integer that does not contain any 0 in its decimal representation.

Given an integer n, return a list of two integers [a, b] where:

    a and b are No-Zero integers.
    a + b = n

The test cases are generated so that there is at least one valid solution. If there are many valid solutions, you can return any of them.

 

Example 1:

Input: n = 2
Output: [1,1]
Explanation: Let a = 1 and b = 1.
Both a and b are no-zero integers, and a + b = 2 = n.

Example 2:

Input: n = 11
Output: [2,9]
Explanation: Let a = 2 and b = 9.
Both a and b are no-zero integers, and a + b = 11 = n.
Note that there are other valid answers as [8, 3] that can be accepted.

 

Constraints:

    2 <= n <= 10^4


*/

class Solution {
private:
    int has_zero(int v, std::vector<int>& zero_exist) {
        if (zero_exist[v] != -1) {
            return zero_exist[v];
        }
        while (v > 0) {
            int d = v % 10;
            v /= 10;

            if (d == 0) {
                return zero_exist[v] = 1;
            }
        }

        return zero_exist[v] = 0;
    }
public:
    vector<int> getNoZeroIntegers(int n) {
        std::vector<int> zero_exist(n + 1, -1);
        for (int i = 1; i < n; ++i) {
            if (has_zero(i, zero_exist) == 0 && has_zero(n - i, zero_exist) == 0) return {i, n - i};            
        }

        return {1, 1};
    }
};
