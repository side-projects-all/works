/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:

    '?' Matches any single character.
    '*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

 

Example 1:

Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:

Input: s = "aa", p = "*"
Output: true
Explanation: '*' matches any sequence.

Example 3:

Input: s = "cb", p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.

 

Constraints:

    0 <= s.length, p.length <= 2000
    s contains only lowercase English letters.
    p contains only lowercase English letters, '?' or '*'.


*/


class Solution {
private:
    bool iterative_remove_extra_star(string& s, string& p) {
        std::string newP = "";

        //clean up extra *
        for (int i = 0; i < p.size(); ++i) {
            if (newP == "" || p[i] != '*') {
                newP += p[i];
            } else if (newP[newP.size() - 1] != '*') {
                newP += p[i];
            }
        }

        int s_len = s.size();
        int p_len = newP.size();

        int si = 0;
        int pi = 0;
        std::vector<std::vector<bool>> mem(s_len + 1, std::vector<bool>(p_len + 1));
        mem[0][0] = true;

        for (int i = 0; i < p_len && newP[i] == '*'; ++i) {
            mem[0][i + 1] = true;
        }

        for (int si = 1; si <= s_len; ++si) {
            for (int pi = 1; pi <= p_len; ++pi) {
                
                if (newP[pi - 1] == '*') {
                    mem[si][pi] = mem[si - 1][pi] || mem[si][pi - 1];

                } else {
                    mem[si][pi] = (s[si - 1] == newP[pi - 1] || newP[pi - 1] == '?') && mem[si - 1][pi - 1];
                }
            }
        }
        
 
        return mem[s_len][p_len];
    }

    bool iterative(string& s, string& p) {
        int sn = s.size();
        int pn = p.size();
        std::vector<std::vector<bool>> dp(sn + 1, std::vector<bool>(pn + 1));
        dp[0][0] = true;

        //important preprocessing
        for (int pl = 0; pl < pn && p[pl] == '*'; ++pl) {
            dp[0][pl + 1] = true;
        }

        for (int sl = 1; sl <= sn; ++sl) {
            for (int pl = 1; pl <= pn; ++pl) {

                if (s[sl - 1] == p[pl - 1] || p[pl - 1] == '?') {
                    dp[sl][pl] = dp[sl - 1][pl - 1];

                } else if (p[pl - 1] == '*') {
                    dp[sl][pl] = dp[sl - 1][pl] || dp[sl][pl - 1];
                }
            }
        }

        return dp[sn][pn];
        
        /*
        int s_len = s.size();
        int p_len = p.size();

        int si = 0;
        int pi = 0;
        std::vector<std::vector<bool>> mem(s_len + 1, std::vector<bool>(p_len + 1));
        mem[0][0] = true;

        for (int i = 0; i < p_len && p[i] == '*'; ++i) {
            mem[0][i + 1] = true;
        }

        for (int si = 1; si <= s_len; ++si) {
            for (int pi = 1; pi <= p_len; ++pi) {
                
                if (p[pi - 1] == '*') {
                    mem[si][pi] = mem[si - 1][pi] || mem[si][pi - 1];

                } else {
                    mem[si][pi] = (s[si - 1] == p[pi - 1] || p[pi - 1] == '?') && mem[si - 1][pi - 1];
                }
            }
        }
        
        return mem[s_len][p_len];
        */
    }

    bool recursive(string& s, string& p) {
        
        std::string newP = "";

        //clean up extra *
        for (int i = 0; i < p.size(); ++i) {
            if (newP == "" || p[i] != '*') {
                newP += p[i];
            } else if (newP[newP.size() - 1] != '*') {
                newP += p[i];
            }
        }

        int s_len = s.size();
        int p_len = newP.size();

        std::vector<std::vector<int>> mem(s_len, std::vector<int>(p_len, -1));

        std::function<bool(int, int)> recurr = [&](int si, int pi) -> bool {
            //base case
            if (pi == p_len) {
                return si == s_len;
            } else if (si == s_len) {
                return newP[pi] == '*' && recurr(si, pi + 1);
            }

            if (mem[si][pi] != -1) {
                return mem[si][pi];
            }
            
            if (newP[pi] == s[si] || newP[pi] == '?') {
                mem[si][pi] = recurr(si + 1, pi + 1);

            } else if (newP[pi] == '*') {
                mem[si][pi] = (recurr(si + 1, pi) || recurr(si, pi + 1));

            } else {
                mem[si][pi] = false;
            }

            return mem[si][pi];
        };

        return recurr(0, 0);
    }
public:
    bool isMatch(string s, string p) {
        //return recursive(s, p);
        return iterative(s, p);
        
        //return iterative_remove_extra_star(s, p);
    }
};