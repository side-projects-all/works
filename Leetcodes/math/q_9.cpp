/*
Given an integer x, return true if x is a
palindrome
, and false otherwise.

 

Example 1:

Input: x = 121
Output: true
Explanation: 121 reads as 121 from left to right and from right to left.

Example 2:

Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.

Example 3:

Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.

 

Constraints:

    -2^31 <= x <= 2^31 - 1

*/

class Solution {
public:
    bool isPalindrome(int x) {

        //no to string
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }

        int reverse = 0;
        while (x > reverse) {
            reverse = reverse * 10 + x % 10;

            x /= 10;
        }

        //if even, then x == reverse
        //if odd, then x == reverse / 10
        return x == reverse || x == reverse / 10;

        //by to string
        /*
        std::string str = std::to_string(x);

        int left = 0;
        int right = str.size() - 1;

        while (left < right) {
            if (str[left] != str[right]) {
                return false;
            }

            ++left;
            --right;
        }

        return true;
        */
    }
};