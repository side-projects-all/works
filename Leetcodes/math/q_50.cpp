/*
mplement pow(x, n), which calculates x raised to the power n (i.e., xn).

 

Example 1:

Input: x = 2.00000, n = 10
Output: 1024.00000

Example 2:

Input: x = 2.10000, n = 3
Output: 9.26100

Example 3:

Input: x = 2.00000, n = -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25

 

Constraints:

    -100.0 < x < 100.0
    -2^31 <= n <= 2^31-1
    n is an integer.
    Either x is not zero or n > 0.
    -10^4 <= xn <= 10^4

*/

class Solution {
private:
    double by_iterative(double& x, long n) {

        if (n < 0) {
            n *= -1;
            x = 1 / x;
        }

        double mul = 1;
        while (n > 0) {

            if (n % 2 == 1) {

                n -= 1;
                mul = x * mul;
            }

            x *= x;
            n >>= 1;    //n /= 2
        }

        return mul;
    }
    double recursive(double x, long n) {
        if (n == 0) {
            return 1.0;
        }

        if (n % 2 == 1) {
            n -= 1;
            return x * recursive(x * x, n / 2);
        }

        return recursive(x * x, n / 2);
    }
    double by_recursive(double& x, long n) {

        if (n < 0) {
            n *= -1;
            x = 1 / x;
        }

        return recursive(x, n);
    }
public:
    double myPow(double x, int n) {
        //return by_recursive(x, n);
        return by_iterative(x, n);
    }
};