/*
Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.

An interleaving of two strings s and t is a configuration where s and t are divided into n and m non-empty substrings respectively, such that:

    s = s1 + s2 + ... + sn
    t = t1 + t2 + ... + tm
    |n - m| <= 1
    The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...

Note: a + b is the concatenation of strings a and b.

 

Example 1:

Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true
Explanation: One way to obtain s3 is:
Split s1 into s1 = "aa" + "bc" + "c", and s2 into s2 = "dbbc" + "a".
Interleaving the two splits, we get "aa" + "dbbc" + "bc" + "a" + "c" = "aadbbcbcac".
Since s3 can be obtained by interleaving s1 and s2, we return true.

Example 2:

Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false
Explanation: Notice how it is impossible to interleave s2 with any other string to obtain s3.

Example 3:

Input: s1 = "", s2 = "", s3 = ""
Output: true

 

Constraints:

    0 <= s1.length, s2.length <= 100
    0 <= s3.length <= 200
    s1, s2, and s3 consist of lowercase English letters.

*/

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.length() + s2.length() != s3.length()) {
            return false;
        }
        
        p_s1 = s1;
        p_s2 = s2;
        p_s3 = s3;
        p_s1Len = s1.length();
        p_s2Len = s2.length();
        p_s3Len = s3.length();
        memo = std::vector<std::vector<bool>>(p_s1Len, std::vector<bool>(p_s2Len, -1));
        
        return topDown(0, 0, "");
    }

private:
    std::string p_s1;
    std::string p_s2;
    std::string p_s3;
    int p_s1Len;
    int p_s2Len;
    int p_s3Len;
    std::vector<std::vector<bool>> memo;
    
    bool topDown(int s1Pos, int s2Pos, std::string res) {
        if (res.compare(p_s3) == 0 && s1Pos == p_s1Len && s2Pos == p_s2Len) {
            return true;
        }
        
        if (memo[s1Pos][s2Pos] != -1) {
            return memo[s1Pos][s2Pos];
        }
        
        bool ans = false;
        if (s1Pos < p_s1Len) {
            ans |= topDown(s1Pos + 1, s2Pos, res + p_s1[s1Pos]);
        }
        if (s2Pos < p_s2Len) {
            ans |= topDown(s1Pos, s2Pos + 1, res + p_s2[s2Pos]);
        }
        
        memo[s1Pos][s2Pos] = ans;
        
        return ans;
    }
};