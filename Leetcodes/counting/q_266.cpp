/*
Given a string s, return true if a permutation of the string could form a
palindrome
and false otherwise.

 

Example 1:

Input: s = "code"
Output: false

Example 2:

Input: s = "aab"
Output: true

Example 3:

Input: s = "carerac"
Output: true

 

Constraints:

    1 <= s.length <= 5000
    s consists of only lowercase English letters.


*/

class Solution {
public:
    bool canPermutePalindrome(string s) {
        int n = s.size();
        if (n == 1) {
            return true;
        }

        std::vector<int> cnt(26);

        for (int i = 0; i < n; ++i) {
            ++cnt[s[i] - 'a'];
        }

        int odd = 0;
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] % 2) {
                ++odd;
            }
        }

        return odd <= 1;
    }
};