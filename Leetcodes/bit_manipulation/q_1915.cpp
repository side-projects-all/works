/*
A wonderful string is a string where at most one letter appears an odd number of times.

    For example, "ccjjc" and "abab" are wonderful, but "ab" is not.

Given a string word that consists of the first ten lowercase English letters ('a' through 'j'), return the number of wonderful non-empty substrings in word. If the same substring appears multiple times in word, then count each occurrence separately.

A substring is a contiguous sequence of characters in a string.

 

Example 1:

Input: word = "aba"
Output: 4
Explanation: The four wonderful substrings are underlined below:
- "aba" -> "a"
- "aba" -> "b"
- "aba" -> "a"
- "aba" -> "aba"

Example 2:

Input: word = "aabb"
Output: 9
Explanation: The nine wonderful substrings are underlined below:
- "aabb" -> "a"
- "aabb" -> "aa"
- "aabb" -> "aab"
- "aabb" -> "aabb"
- "aabb" -> "a"
- "aabb" -> "abb"
- "aabb" -> "b"
- "aabb" -> "bb"
- "aabb" -> "b"

Example 3:

Input: word = "he"
Output: 2
Explanation: The two wonderful substrings are underlined below:
- "he" -> "h"
- "he" -> "e"

 

Constraints:

    1 <= word.length <= 10^5
    word consists of lowercase English letters from 'a' to 'j'.

*/

class Solution {
public:
    long long wonderfulSubstrings(string word) {
        int N = word.size();
        std::unordered_map<int, int> m;

        m[0] = 1;
        int mask = 0;
        long long ans = 0;

        for (int i = 0; i < N; ++i) {
            char c = word[i];
            int bit = c - 'a';

            //the parity mask of the current prefix
            //if the letter never appeared before, the position of the letter in mask would be 1
            //if the letter had appeared before, the position of the letter in mask would be 0
            mask ^= (1 << bit); 

            //if the letter had appeared before, it means you would not add a new bit into the mask, 
            //you would just cancel a bit in original mask, 
            //then of course, you had already record the mask with its counts, 
            //so you could find it.
            //counting even here
            if (m.find(mask) != m.end()) {
                ans += m[mask];
                ++m[mask];
            } else {
                m[mask] = 1;
            }

            //for counting exactly one letter appears an odd number of times
            for (int odd_c = 0; odd_c < 10; ++odd_c) {
                int val = mask ^ (1 << odd_c);
                
                if (m.find(val) != m.end()) {
                    ans += m[val];
                }
            }
        }

        return ans;
    }
};