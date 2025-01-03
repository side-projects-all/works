/*
Given a string s, find the length of the longest substring without repeating characters.

 

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

 

Constraints:

    0 <= s.length <= 5 * 10^4
    s consists of English letters, digits, symbols and spaces.


*/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int len = s.size();
        int b = 0;
        int e = 0;
        int longest = 0;
        //std::unordered_map<char, int> found;
        std::array<int, 128> found{ 0 };

        while (e < len) {
            found[s[e]]++;

            while (found[s[e]] > 1) {
                --found[s[b]];
                ++b;
            }
            
            longest = std::max(longest, e - b + 1);
            ++e;
        }

        return longest;
    }
};