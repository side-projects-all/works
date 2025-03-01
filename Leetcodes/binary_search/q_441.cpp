/*
You have n coins and you want to build a staircase with these coins. The staircase consists of k rows where the ith row has exactly i coins. The last row of the staircase may be incomplete.

Given the integer n, return the number of complete rows of the staircase you will build.

 

Example 1:

Input: n = 5
Output: 2
Explanation: Because the 3rd row is incomplete, we return 2.

Example 2:

Input: n = 8
Output: 3
Explanation: Because the 4th row is incomplete, we return 3.

 

Constraints:

    1 <= n <= 2^31 - 1


*/

class Solution {
public:
    int arrangeCoins(int n) {
        if (n <= 2) {
            return 1;
        }
        if (n == 3) {
            return 2;
        }

        long left = 4;
        long right = n / 2;

        while (left <= right) {
            long mid = left + (right - left) / 2;
            long diff = mid * (mid + 1) / 2 - n;

            if (diff == 0) {
                return (int)mid;
            }

            if (diff > 0) {
                right = mid - 1;
                
            } else {
                left = mid + 1;
            }
        }

        return (int)right;
    }
};