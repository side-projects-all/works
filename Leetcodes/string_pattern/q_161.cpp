/*
Given two strings s and t, return true if they are both one edit distance apart, otherwise return false.

A string s is said to be one distance apart from a string t if you can:

    Insert exactly one character into s to get t.
    Delete exactly one character from s to get t.
    Replace exactly one character of s with a different character to get t.

 

Example 1:

Input: s = "ab", t = "acb"
Output: true
Explanation: We can insert 'c' into s to get t.

Example 2:

Input: s = "", t = ""
Output: false
Explanation: We cannot get t from s by only one step.

 

Constraints:

    0 <= s.length, t.length <= 10^4
    s and t consist of lowercase letters, uppercase letters, and digits.


*/

class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        
        int s_len = s.size();
        int t_len = t.size();
        int len_diff = std::abs(s_len - t_len);
        if (len_diff > 1) {
            return false;

        } 
        
        //the same length
        if (len_diff == 0) {

            int cnt = 0;
            for (int i = 0; i < s_len; ++i) {

                if (s[i] != t[i]) {
                    ++cnt;
                    
                    if (cnt > 1) {
                        return false;
                    }
                }
            }

            return cnt == 1;  //for no change case
        }

        //for len diff is 1, you can only add a char or delete a char 
        for (int i = 0; i < std::min(s_len, t_len); ++i) {

            if (s[i] != t[i]) {

                //compare the rest of longer string with the the shorter string
                if (s_len < t_len) {
                    return s.substr(i, s_len - i) == t.substr(i + 1, t_len - i - 1);
                } else {
                    return s.substr(i + 1, s_len - i - 1) == t.substr(i, t_len - i);
                }
            }
        }
        
        return true;
        
        /*
        int sLen = s.size();
        int tLen = t.size();

        //assume length of s is always shorter than or equal to t
        if (sLen > tLen) {
            return isOneEditDistance(t, s);
        }

        //edge case: difference of length is larger than 1
        if ((tLen - sLen) > 1) {
            return false;
        }

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] != t[i]) {

                if (tLen == sLen) {
                    return s.substr(i + 1, s.size() - i - 1) == t.substr(i + 1, t.size() - i - 1);
                } else {
                     return s.substr(i, s.size() - i) == t.substr(i + 1, t.size() - i - 1);
                }
            }
        }


        return (sLen + 1) == tLen;
        */
    }
};