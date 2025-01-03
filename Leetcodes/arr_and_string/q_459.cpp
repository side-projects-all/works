/*
Given a string s, check if it can be constructed by taking a substring of it and appending multiple copies of the substring together.

 

Example 1:

Input: s = "abab"
Output: true
Explanation: It is the substring "ab" twice.

Example 2:

Input: s = "aba"
Output: false

Example 3:

Input: s = "abcabcabcabc"
Output: true
Explanation: It is the substring "abc" four times or the substring "abcabc" twice.

 

Constraints:

    1 <= s.length <= 10^4
    s consists of lowercase English letters.


*/

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int n = s.size();

        for (int i = 1; i <= (n / 2); ++i) {

            if (n % i == 0) {
                std::string substr = s.substr(0, i);
                bool isRepeated = true;

                for (int j = i; j < n; j += i) {
                    std::string target = s.substr(j, i);
                    if (substr != target) {
                        isRepeated = false;
                        break;
                    }
                }

                if (isRepeated) {
                    return true;
                }
            }
        }

        return false;
    }
};