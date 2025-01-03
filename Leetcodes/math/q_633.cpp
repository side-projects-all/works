/*
Given a non-negative integer c, decide whether there're two integers a and b such that a2 + b2 = c.

 

Example 1:

Input: c = 5
Output: true
Explanation: 1 * 1 + 2 * 2 = 5

Example 2:

Input: c = 3
Output: false

 

Constraints:

    0 <= c <= 2^31 - 1


*/

class Solution {
private:
    /*
    double find_sqrt(int c) {
        if (c <= 1) {
            return c;
        }

        double c0 = c;
        double x0 = c;
        double x1 = (x0 + c0 / x0) / 2.0;

        while (std::abs(x0 - x1) >= 1) {
            x0 = x1;
            x1 = (x0 + c0 / x0) / 2.0;
        }

        return x1;
    }
    */

    bool byRoots(int c) {
        long long int i = 1;
        long long j = std::sqrt(c);
        if (j * j == c) {
            return true;
        }
        
        while(i <= j) {
           long long sum = (i * i) + (j * j);
           if(sum == c) {
                return true;

           } else if(sum < c) {
                i++;
           } else {
                j--;
           }           
        }

        return false;
    }

    bool byFermatThm(int c) {
        for (int i = 2; i * i <= c; ++i) {
            int cnt = 0;

            if (c % i == 0) {
                while (c % i == 0) {
                    ++cnt;
                    c /= i;
                }

                if (i % 4 == 3 && cnt % 2 != 0) {
                    return false;
                }
            }
        }

        return c % 4 != 3;
    }

    bool bySqrt(int c) {

        for (long sqrt1 = 0; sqrt1 * sqrt1 <= c; ++sqrt1) {

            double sqrt2 = std::sqrt(c - sqrt1 * sqrt1);
            if (sqrt2 == (int)sqrt2) {
                return true;
            }
        }

        return false;
    }
public:
    bool judgeSquareSum(int c) {
        if (c <= 2) {
            return true;
        }

        //return bySqrt(c);
        //return byFermatThm(c);
        
        return byRoots(c);
    }
};