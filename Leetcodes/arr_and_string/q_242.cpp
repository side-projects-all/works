/*
Given two strings s and t, return true if t is an anagram of s, and false otherwise.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

 

Example 1:

Input: s = "anagram", t = "nagaram"
Output: true

Example 2:

Input: s = "rat", t = "car"
Output: false

 

Constraints:

    1 <= s.length, t.length <= 5 * 10^4
    s and t consist of lowercase English letters.

*/

class Solution {
public:
    bool isAnagram(string s, string t) {
        /*
        std::sort(s.begin(), s.end());
        std::sort(t.begin(), t.end());

        return t == s;
        */

        //by count
        if (s.size() != t.size()) {
            return false;
        }

        int alphabet[26] = { 0 };
        for (int i = 0; i < s.size(); ++i) {
            
            ++alphabet[s[i] - 'a'];
            --alphabet[t[i] - 'a'];
        }

        for (int val : alphabet) {
            if (val > 0) {
                return false;
            }
        }

        return true;
    }
};