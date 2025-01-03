/*
Given an integer n, return true if it is a power of three. Otherwise, return false.

An integer n is a power of three, if there exists an integer x such that n == 3x.

 

Example 1:

Input: n = 27
Output: true
Explanation: 27 = 33

Example 2:

Input: n = 0
Output: false
Explanation: There is no x where 3x = 0.

Example 3:

Input: n = -1
Output: false
Explanation: There is no x where 3x = (-1).

 

Constraints:

    -2^31 <= n <= 2^31 - 1

 
*/

class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n < 1) {
            return false;
        }

        //naive
        /*
        long val = 1;
        while (val <= n) {

            if (val == n) {
                return true;
            }

            val *= 3;
        }

        return false;
        */

        return 1162261467 % n == 0;
    }
};