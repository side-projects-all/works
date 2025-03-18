/*
Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:

    '.' Matches any single character.​​​​
    '*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

 

Example 1:

Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:

Input: s = "aa", p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".

Example 3:

Input: s = "ab", p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".

 

Constraints:

    1 <= s.length <= 20
    1 <= p.length <= 20
    s contains only lowercase English letters.
    p contains only lowercase English letters, '.', and '*'.
    It is guaranteed for each appearance of the character '*', there will be a previous valid character to match.


*/

class Solution {
private:
    bool iterative(std::string& s, std::string& p) {
        int sn = s.size();
        int pn = p.size();

        std::vector<std::vector<bool>> dp(sn + 1, std::vector<bool>(pn + 1));
        dp[0][0] = true;

        for (int len = 2; len <= pn; ++len) {

            if (p[len - 1] == '*') {
                dp[0][len] = dp[0][len - 2];
            }
        }

        //for every length of s matches every length of p
        for (int sl = 1; sl <= sn; ++sl) {
            for (int pl = 1; pl <= pn; ++pl) {

                if (s[sl - 1] == p[pl - 1] || p[pl - 1] == '.') {
                    dp[sl][pl] = dp[sl - 1][pl - 1];

                } else if (p[pl - 1] == '*') {

                    if (s[sl - 1] == p[pl - 2] || p[pl - 2] == '.') {
                        dp[sl][pl] = dp[sl][pl - 2] || dp[sl - 1][pl];

                    } else {
                        dp[sl][pl] = dp[sl][pl - 2];
                    }
                }
            }
        }

        return dp[sn][pn];
        
        /*
        int sn = s.size();
        int pn = p.size();

        std::vector<std::vector<bool>> dp(sn + 1, std::vector<bool>(pn + 1));
        dp[sn][pn] = true;  //both are empty string, then they are equal, so it is true

        //from the recursion, the idea of getting suffix to compare
        for (int si = sn; si >= 0; --si) {
            for (int pi = pn - 1; pi >= 0; --pi) {
                bool curr = si < sn && (s[si] == p[pi] || p[pi] == '.');

                if (pi + 1 < pn && p[pi + 1] == '*') {
                    dp[si][pi] = (dp[si][pi + 2] || (curr && dp[si + 1][pi]));
                } else {
                    dp[si][pi] = (curr && dp[si + 1][pi + 1]);
                }
            }
        }

        return dp[0][0];
        */
    }
    bool recursive(std::string& s, std::string& p) {
        int sN = s.size();
        int pN = p.size();
        std::vector<std::vector<int>> mem(sN + 1, std::vector<int>(pN + 1, -1));

        std::function<bool(int, int)> recurr = [&](int sI, int pI) -> bool {
            //base case
            if (pI == pN) {
                return sI == sN;
            }

            if (mem[sI][pI] != -1) {
                return mem[sI][pI];
            }

            bool currMatch = (sI < sN && (p[pI] == s[sI] || p[pI] == '.'));

            if (pI + 1 < pN && p[pI + 1] == '*') {
                //'*' means Matches zero or more of the preceding element
                //so "recurr(sI, pI + 2)" means we treat it like zero preceding element, 
                //or like "currMatch && recurr(sI + 1, pI)" means precedent one matched, 
                //and we continue to next character to check if it would be the same
                mem[sI][pI] = recurr(sI, pI + 2) || (currMatch && recurr(sI + 1, pI));
            } else {
                mem[sI][pI] = currMatch && recurr(sI + 1, pI + 1);
            }

            return mem[sI][pI];
        };

        return recurr(0, 0);
    }
public:
    bool isMatch(string s, string p) {
        //return recursive(s, p);
        return iterative(s, p);
    }
};