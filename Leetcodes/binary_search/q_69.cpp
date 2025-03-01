/*
Given a non-negative integer x, return the square root of x rounded down to the nearest integer. The returned integer should be non-negative as well.

You must not use any built-in exponent function or operator.

    For example, do not use pow(x, 0.5) in c++ or x ** 0.5 in python.

 

Example 1:

Input: x = 4
Output: 2
Explanation: The square root of 4 is 2, so we return 2.

Example 2:

Input: x = 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since we round it down to the nearest integer, 2 is returned.

 

Constraints:

    0 <= x <= 2^31 - 1


*/

class Solution {
private:
    int by_bit_ops(int x) {
        if (x < 2) {
            return x;
        }

        //by bit operation
        int left = by_bit_ops(x >> 2) << 1;
        int right = left + 1;

        //left is smaller, right is larger
        //if right * right were larger than x, we choose smaller, vice versa.
        return ((long)right * right > x) ? left : right;
    }
    int by_newtons_method(int& x) {
        //newton's method
        double x0 = x;
        double x1 = (x0 + x / x0) / 2.0;

        while (std::abs(x0 - x1) >= 1) {
            x0 = x1;
            x1 = (x0 + x / x0) / 2.0;
        }

        return (int)x1;
    }
    int by_binary_search(int& x) {
        int num = 0;
        int upper = x / 2;
        int low = 2;
        long sq = 0L;
        while (low <= upper) {
            num = low + (upper - low) / 2;
            sq = (long)num * num;
             
            if (sq > x) {
                //sq is too large, so we reduce the pivot(num)
                upper = num - 1;
            } else if (sq < x) {
                //sq is too small, so we add the pivot(num)
                low = num + 1;
            } else {
                return num;
            }
        }

        return upper; //why not low? because low will exceed upper!! we only need the value when low == upper
    }

public:
    int mySqrt(int x) {
        if (x < 2) {
            return x;
        }

        //return by_bit_ops(x);
        //return by_newtons_method(x);
        return by_binary_search(x);
    }
};