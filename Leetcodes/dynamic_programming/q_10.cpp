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
        int sN = s.size();
        int pN = p.size();
        std::vector<std::vector<bool>> mem(sN + 1, std::vector<bool>(pN + 1, 0));
        mem[sN][pN] = true;

        for (int sI = sN; sI >= 0; --sI) {
            for (int pI = pN - 1; pI >= 0; --pI) {
                bool currMatch = (sI < sN && (p[pI] == s[sI] || p[pI] == '.'));

                if (pI + 1 < pN && p[pI + 1] == '*') {
                    mem[sI][pI] = (mem[sI][pI + 2]) || (currMatch && mem[sI + 1][pI]);
                    
                } else {
                    mem[sI][pI] = currMatch && mem[sI + 1][pI + 1];
                }
            }
        }

        return mem[0][0];
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