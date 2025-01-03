/*
Given a string s and an integer k, return the length of the longest
substring
of s that contains at most k distinct characters.

 

Example 1:

Input: s = "eceba", k = 2
Output: 3
Explanation: The substring is "ece" with length 3.

Example 2:

Input: s = "aa", k = 1
Output: 2
Explanation: The substring is "aa" with length 2.

 

Constraints:

    1 <= s.length <= 5 * 10^4
    0 <= k <= 50


*/

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        int len = s.size();
        if (len <= k) {
            return len;
        }

        int b = 0;
        int longest = 0;
        std::unordered_map<char, int> window;
        for (int e = 0; e < len; ++e) {
            ++window[s[e]];

            while (window.size() > k) {
                --window[s[b]];

                if (window[s[b]] == 0) {
                    window.erase(s[b]);
                }

                ++b;
            }

            longest = std::max(longest, e - b + 1);
        }

        return longest;
    }
};