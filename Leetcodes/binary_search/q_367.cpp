/*
Given a positive integer num, return true if num is a perfect square or false otherwise.

A perfect square is an integer that is the square of an integer. In other words, it is the product of some integer with itself.

You must not use any built-in library function, such as sqrt.

 

Example 1:

Input: num = 16
Output: true
Explanation: We return true because 4 * 4 = 16 and 4 is an integer.

Example 2:

Input: num = 14
Output: false
Explanation: We return false because 3.742 * 3.742 = 14 and 3.742 is not an integer.

 

Constraints:

    1 <= num <= 2^31 - 1


*/

class Solution {
private:
    bool newtonMethod(int num) {
        if (num < 2) {
            return true;
        }

        long x = num / 2;
        while (x * x > num) {
            x = (x + num / x) / 2;
        }

        return (x * x == num);
    }

    bool binarySearch(int num) {
        if (num < 2) {
            return true;
        }

        int left = 1;
        int right = num / 2;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if ((long)mid * mid == (long)num) {
                return true;

            } else if ((long)mid * mid > (long)num) {
                right = mid - 1;

            } else {
                left = mid + 1;
            }
        }

        return false;
    }
public:
    bool isPerfectSquare(int num) {
        //return binarySearch(num);

        return newtonMethod(num);
    }
};