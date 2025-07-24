/*
Given two integers left and right that represent the range [left, right], return the bitwise AND of all numbers in this range, inclusive.

 

Example 1:

Input: left = 5, right = 7
Output: 4

Example 2:

Input: left = 0, right = 0
Output: 0

Example 3:

Input: left = 1, right = 2147483647
Output: 0

 

Constraints:

    0 <= left <= right <= 2^31 - 1


*/

class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        /*
        int shift = 0;

        while (left < right) {
            left = left >> 1;
            right = right >> 1;            

            ++shift;
        }

        return left << shift;
        */

        //Brian Kernighan's Algorithm
        while (left < right) {
            right = right & (right - 1);
        }

        return left & right;
    }
};