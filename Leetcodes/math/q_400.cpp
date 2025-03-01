/*
Given an integer n, return the nth digit of the infinite integer sequence [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...].

 

Example 1:

Input: n = 3
Output: 3

Example 2:

Input: n = 11
Output: 0
Explanation: The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0, which is part of the number 10.

 

Constraints:

    1 <= n <= 2^31 - 1


*/

class Solution {
public:
    int findNthDigit(int n) {
        //begin in one digit interval
        long digit = 9;
        int len = 1;
        int first = 1;

        while (n > digit * len) {
            n -= digit * len;
            ++len;  //to next digit interval
            first *= 10;
            digit *= 10;
        }

        first += (n - 1) / len;
        std::string num = std::to_string(first);

        return num[((n - 1) % len)] - '0';
    }
};