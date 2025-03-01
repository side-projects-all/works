/*
Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.

 

Example 1:

Input: s = "leetcode"
Output: 0

Example 2:

Input: s = "loveleetcode"
Output: 2

Example 3:

Input: s = "aabb"
Output: -1

 

Constraints:

    1 <= s.length <= 10^5
    s consists of only lowercase English letters.


*/

class Solution {
public:
    int firstUniqChar(string s) {
        /*
        std::vector<int> chars(26, 100000);
        int min_i = 0;
        chars[s[0] - 97] = 1;

        for (int i = 1; i < s.size(); ++i) {

            if (chars[s[i] - 97] == 100000) {
                chars[s[i] - 97] = 1;
            } else {
                ++chars[s[i] - 97];
            }
            
        }

        for (int i = 0; i < s.size(); ++i) {
            if (chars[s[i] - 97] == 1) {
                return i;
            }
        }

        return -1;
        */
        
        std::vector<int> cnt(26);
        std::vector<int> indices(26);

        for (int i = 0; i < s.size(); ++i) {
            ++cnt[s[i] - 'a'];
            indices[s[i] - 'a'] = i;
        }

        int min_i = 100000;
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] == 1) {
                min_i = std::min(min_i, indices[i]);
            }
        }

        return min_i == 100000 ? -1 : min_i;
    }
};