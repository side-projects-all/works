/*
Given two strings s and p, return an array of all the start indices of p's
anagrams
in s. You may return the answer in any order.

 

Example 1:

Input: s = "cbaebabacd", p = "abc"
Output: [0,6]
Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".

Example 2:

Input: s = "abab", p = "ab"
Output: [0,1,2]
Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

 

Constraints:

    1 <= s.length, p.length <= 3 * 10^4
    s and p consist of lowercase English letters.


*/

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int len_p = p.size();
        int len_s = s.size();
        if (len_s < len_p) {
            return {};
        }
        
        std::array<int, 26> p_cnt;
        for (int i = 0; i < len_p; ++i) {
            ++p_cnt[p[i] - 'a'];
        }

        std::vector<int> ans;
        int b = 0;
        int e = 0;
        int cnt = len_p;

        while (e < len_s) {
            if (p_cnt[s[e] - 'a'] > 0) {
                --cnt;
            }

            --p_cnt[s[e] - 'a'];

            if (cnt == 0) {
                ans.push_back(b);
            }

            ++e;
            if (e >= len_p) {
                if (p_cnt[s[b] - 'a'] >= 0) {
                    ++cnt;
                }

                ++p_cnt[s[b] - 'a'];
                ++b;
            }
        }


        return ans;
    }
};