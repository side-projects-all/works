/*
A string is called a happy prefix if is a non-empty prefix which is also a suffix (excluding itself).

Given a string s, return the longest happy prefix of s. Return an empty string "" if no such prefix exists.

 

Example 1:

Input: s = "level"
Output: "l"
Explanation: s contains 4 prefix excluding itself ("l", "le", "lev", "leve"), and suffix ("l", "el", "vel", "evel"). The largest prefix which is also suffix is given by "l".

Example 2:

Input: s = "ababab"
Output: "abab"
Explanation: "abab" is the largest prefix which is also suffix. They can overlap in the original string.

 

Constraints:

    1 <= s.length <= 10^5
    s contains only lowercase English letters.


*/

class Solution {
public:
    string longestPrefix(string s) {
        int N = s.size();
        std::vector<int> longest_border(N);
        int prev = 0;
        int i = 1;

        //this is the preprocessing for KMP algorithm to get longest_border
        while (i < N) {
            if (s[i] == s[prev]) {
                ++prev;
                longest_border[i] = prev;
                ++i;
            } else {
                if (prev == 0) {
                    longest_border[i] = 0;
                    ++i;
                } else {
                    prev = longest_border[prev - 1];
                }
            }

        }

        return s.substr(0, prev);
    }
};