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
    -231 <= n <= 231-1
    n is an integer.
    Either x is not zero or n > 0.
    -104 <= xn <= 104

*/

class Solution {
public:
    double myPow(double x, int n) {

        //return recursive(x, n);
        return iterative(x, n);
    }

private:
    double iterative(double x, long long n) {
        if (n == 0) {
            return 1.0;
        }

        if (n < 0) {
            n = -1 * n;
            x = 1.0 / x;
        }

        double result = 1;
        while (n > 0) {

            //for n is odd, reduce n by 1
            if (n % 2 == 1) {
                result = result * x;
                n -= 1;
            }

            x = x * x;
            n = n / 2;
        }

        return result;
    }

    double recursive(double x, long long n) {
        
        if (n == 0) {
            return 1.0;
        }

        if (n < 0) {
            return 1.0 / recursive(x, -1 * n);
        }

        //binary exponential 
        //this is an important skill!!
        double val = 0;
        if (n % 2 != 0) {
            val = x * recursive(x * x, (n - 1) / 2);
        } else {
            val = recursive(x * x, n / 2);
        }

        return val;
    }
};