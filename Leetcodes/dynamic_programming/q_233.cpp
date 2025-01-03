/*
Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.

 

Example 1:

Input: n = 13
Output: 6

Example 2:

Input: n = 0
Output: 0

 

Constraints:

    0 <= n <= 10^9


*/

class Solution {
public:
    int countDigitOne(int n) {
        if (n <= 1) {
            return n;
        }

        int cnt = 0;
        for (long long i = 1; i <= n; i *= 10) {
            long long divider = i * 10;
            cnt += (n / divider) * i + std::min(std::max(n % divider - i + 1, 0LL), i);
        }

        return cnt;
    }
};