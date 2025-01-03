/*
Given the string s, return the size of the longest substring containing each vowel an even number of times. That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.

 

Example 1:

Input: s = "eleetminicoworoep"
Output: 13
Explanation: The longest substring is "leetminicowor" which contains two each of the vowels: e, i and o and zero of the vowels: a and u.

Example 2:

Input: s = "leetcodeisgreat"
Output: 5
Explanation: The longest substring is "leetc" which contains two e's.

Example 3:

Input: s = "bcbcbc"
Output: 6
Explanation: In this case, the given string "bcbcbc" is the longest because all vowels: a, e, i, o and u appear zero times.

 

Constraints:

    1 <= s.length <= 5 x 10^5
    s contains only lowercase English letters.


*/

class Solution {
public:
    int findTheLongestSubstring(string s) {
        int prefix_xor = 0;
        int char_map[26] = { 0 };
        char_map['a' - 'a'] = 1;
        char_map['e' - 'a'] = 2;
        char_map['i' - 'a'] = 4;
        char_map['o' - 'a'] = 8;
        char_map['u' - 'a'] = 16;

        std::vector<int> mp(32, -1);
        int ans = 0;
        for (int i = 0; i < s.size(); ++i) {
            prefix_xor ^= char_map[s[i] - 'a'];

            if (mp[prefix_xor] == -1 && prefix_xor != 0) {
                mp[prefix_xor] = i;
            }

            ans = std::max(ans, i - mp[prefix_xor]);
        }

        return ans;
    }
};