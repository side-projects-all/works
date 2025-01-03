/*
Given a string num which represents an integer, return true if num is a strobogrammatic number.

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

 

Example 1:

Input: num = "69"
Output: true

Example 2:

Input: num = "88"
Output: true

Example 3:

Input: num = "962"
Output: false

 

Constraints:

    1 <= num.length <= 50
    num consists of only digits.
    num does not contain any leading zeros except for zero itself.


*/

class Solution {
public:
    bool isStrobogrammatic(string num) {
        std::unordered_map<char, char> m{ {'6', '9'}, {'1', '1'}, {'0', '0'}, {'9', '6'}, {'8', '8'} };

        for (int i = 0; i <= num.size() / 2; ++i) {

            if (m.find(num[i]) == m.end()) {
                return false;
            } else {
                int e = num.size() - i - 1;

                if (m.find(num[e]) == m.end()) {
                    return false;

                } else if (m[num[e]] != num[i]) {
                    return false;
                }
            }
        }

        return true;
    }
};