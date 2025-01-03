/*
A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.

 

Example 1:

Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.

Example 2:

Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.

Example 3:

Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.

 

Constraints:

    1 <= s.length <= 2 * 10^5
    s consists only of printable ASCII characters.


*/

class Solution {
public:
    bool isPalindrome(string s) {
        if (s.size() == 1) {
            return true;
        }

        int left = 0;
        int right = s.size() - 1;

        while (left < right) {

            while (left < s.size() && !std::isalnum(s[left])) {
                ++left;
            }

            while (right >= 0 && !std::isalnum(s[right])) {
                --right;
            }

            if (left < s.size() && right >= 0) {
                if (std::isupper(s[left])) {
                    s[left] = std::tolower(s[left]);
                }

                if (std::isupper(s[right])) {
                    s[right] = std::tolower(s[right]);
                }

                if (s[left] != s[right]) {
                    return false;
                }
            }

            --right;
            ++left;
        }

        return true;
    }
};