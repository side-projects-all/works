/*
You are given a string s and an integer k.

Determine if there exists a substring of length exactly k in s that satisfies the following conditions:

    The substring consists of only one distinct character (e.g., "aaa" or "bbb").
    If there is a character immediately before the substring, it must be different from the character in the substring.
    If there is a character immediately after the substring, it must also be different from the character in the substring.

Return true if such a substring exists. Otherwise, return false.
A substring is a contiguous non-empty sequence of characters within a string.

 

Example 1:

Input: s = "aaabaaa", k = 3

Output: true

Explanation:

The substring s[4..6] == "aaa" satisfies the conditions.

    It has a length of 3.
    All characters are the same.
    The character before "aaa" is 'b', which is different from 'a'.
    There is no character after "aaa".

Example 2:

Input: s = "abc", k = 2

Output: false

Explanation:

There is no substring of length 2 that consists of one distinct character and satisfies the conditions.

 

Constraints:

    1 <= k <= s.length <= 100
    s consists of lowercase English letters only.


*/

class Solution {
private:

public:
    bool hasSpecialSubstring(string s, int k) {
        int n = s.size();
        if (n == 1) {
            return true;
        }
        
        if (n == k) {
            for (int i = 1; i < n; ++i) {
                if (s[i] != s[i - 1]) {
                    return false;
                }
            }
            
            return true;
        }
        
        std::unordered_map<char, int> m;
        for (int i = 0; i < k; ++i) {
            ++m[s[i]];
        }
        
        if (m.size() == 1 && k < n && s[k - 1] != s[k]) {
            return true;
        }
        
        for (int i = k; i < n; ++i) {
            
            --m[s[i - k]];
            if (m[s[i - k]] == 0) {
                m.erase(s[i - k]);
            }
            ++m[s[i]];
            
            if (m.size() == 1) {
                
                if (i == n - 1) {
                    if (s[i - k + 1] != s[i - k]) {
                        return true;
                    }
                    
                } else {
                    if (s[i - k + 1] != s[i - k] && s[i] != s[i + 1]) {
                        return true;
                    }
                }
            }
            
        }
        
        return false;
    }
};