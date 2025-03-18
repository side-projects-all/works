/*
Given an integer n, return true if it is possible to represent n as the sum of distinct powers of three. Otherwise, return false.

An integer y is a power of three if there exists an integer x such that y == 3x.

 

Example 1:

Input: n = 12
Output: true
Explanation: 12 = 31 + 32

Example 2:

Input: n = 91
Output: true
Explanation: 91 = 30 + 32 + 34

Example 3:

Input: n = 21
Output: false

 

Constraints:

    1 <= n <= 10^7


*/

class Solution {
public:
    bool checkPowersOfThree(int n) {
        int pow = (std::log(n) / std::log(3)) + 1;  //max pow depends on log3(n)

        while (n > 2) {
            int max_val = std::pow(3, pow);
            if (n - max_val >= 0) {
                n -= max_val;
            }

            if (n - max_val >= 0) {
                return false;
            }

            --pow;
        }

        return n <= 1;
    }
};