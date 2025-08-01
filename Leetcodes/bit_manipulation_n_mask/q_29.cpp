/*
Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.

The integer division should truncate toward zero, which means losing its fractional part. For example, 8.345 would be truncated to 8, and -2.7335 would be truncated to -2.

Return the quotient after dividing dividend by divisor.

Note: Assume we are dealing with an environment that could only store integers within the 32-bit signed integer range: [−231, 231 − 1]. For this problem, if the quotient is strictly greater than 231 - 1, then return 231 - 1, and if the quotient is strictly less than -231, then return -231.

 

Example 1:

Input: dividend = 10, divisor = 3
Output: 3
Explanation: 10/3 = 3.33333.. which is truncated to 3.

Example 2:

Input: dividend = 7, divisor = -3
Output: -2
Explanation: 7/-3 = -2.33333.. which is truncated to -2.

 

Constraints:

    -2^31 <= dividend, divisor <= 2^31 - 1
    divisor != 0


*/

const static int HALF_INT_MIN = -1073741824;

class Solution {
private:
    int by_long_div_in_base2(int& dividend, int& divisor) {
        //two corner cases!
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }

        if (dividend == INT_MIN && divisor == 1) {
            return INT_MIN;
        }

        //count the number of negative sign, to decide if we need to convert at the end, 
        //all pos or neg, we need to convert at the end
        int neg = 2;
        if (dividend > 0) {
            --neg;
            dividend = -dividend;
        }
        if (divisor > 0) {
            --neg;
            divisor = -divisor;
        }

        //max bits you can move left for divisor
        int max_bits = 0;
        while (divisor >= HALF_INT_MIN && divisor + divisor >= dividend) {
            ++max_bits;
            divisor += divisor;
        } 

        int quotient = 0;
        for (int bit = max_bits; bit >= 0; --bit) {

            //remember, it is under negative situation
            if (divisor >= dividend) {
                quotient -= (1 << bit);
                dividend -= divisor;
            }

            //possibly a odd divisor, so we add 1
            divisor = (divisor + 1) >> 1;
        }

        if (neg != 1) {
            quotient = -quotient;
        }

        return quotient;
    }
public:
    int divide(int dividend, int divisor) {
        return by_long_div_in_base2(dividend, divisor);
    }
};
