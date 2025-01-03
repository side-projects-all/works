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
public:
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) { return 1; }

        int total = 10;
        int prod = 9; // 1 digit * 9
        for (int d = 2; d < n + 1; ++d) {
            total += prod * (11 - d);
            prod *= 11 - d;
        }

        return total;
    }
};