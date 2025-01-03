/*
Given two strings s and t, return true if s is a subsequence of t, or false otherwise.

A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).

 

Example 1:

Input: s = "abc", t = "ahbgdc"
Output: true

Example 2:

Input: s = "axc", t = "ahbgdc"
Output: false

 

Constraints:

    0 <= s.length <= 100
    0 <= t.length <= 10^4
    s and t consist only of lowercase English letters.

 
Follow up: Suppose there are lots of incoming s, say s1, s2, ..., sk where k >= 109, 
and you want to check one by one to see if t has its subsequence. In this scenario, how would you change your code?
*/

class Solution {
private:
    ////divide and conquer with greedy
    bool recursive_dcg(std::string& s, std::string& t, int& sIndex, int& tIndex) {
        if (sIndex == s.size()) {
            return true;
        }

        if (tIndex == t.size()) {
            return false;
        }

        //based on those recursive rules:
        //isSubsequence(source, target) = isSubsequence(source[1:], target[1:])    same
        //                                isSubsequence(source, target[1:])​        not the same

        //increase source index when equals to target index
        if (s[sIndex] == t[tIndex]) {
            ++sIndex;
        }

        //both situation would need to increase target index
        ++tIndex;

        //tail recursion
        return recursive_dcg(s, t, sIndex, tIndex);
    }

    bool twoPointer(std::string& s, std::string& t) {

        int sIndex = 0;
        int tIndex = 0;

        while (sIndex < s.size() && tIndex < t.size()) {
            if (s[sIndex] == t[tIndex]) {
                ++sIndex;
            }

            ++tIndex;
        }

        if (sIndex == s.size()) {
            return true;
        }

        return false;
    }

    bool dp(std::string& s, std::string& t) {
        if (s.size() == 0) {
            return true;
        }

        std::vector<std::vector<int>> dp(s.size() + 1, std::vector<int>(t.size() + 1, 0));
        for (int col = 1; col <= t.size(); ++col) {

            for (int row = 1; row <= s.size(); ++row) {
                if (s[row - 1] == t[col - 1]) {

                    //if they were equal, then we have 1 more to delete
                    dp[row][col] = dp[row - 1][col - 1] + 1;

                } else {
                    //if they were not equal, we want the maximum of pre-situations, 
                    //that are max values of pre-target(fixed source) and pre-source(fixed target)
                    //because we are greedy, we want to maximize what could delete
                    dp[row][col] = std::max(dp[row][col - 1], dp[row - 1][col]);
                }
            }

            //when some dp value equals to source size, it means we could delete some characters in target, 
            //and turn it into source
            if (dp[s.size()][col] == s.size()) {
                return true;
            }
        }

        return false;
    }
public:
    bool isSubsequence(string s, string t) {
        
        //dynamic programming
        //return dp(s, t);

        //two pointer
        //return twoPointer(s, t);

        //divide and conquer with greedy
        /*
        int sIndex = 0;
        int tIndex = 0;
        return recursive_dcg(s, t, sIndex, tIndex);
        */

        //my naive solution
        /*
        std::string::size_type index = -1;
        for (int i = 0; i < s.size(); ++i) {
            //find from last position + 1
            index = t.find(s[i], index + 1);

            if (index == std::string::npos || (t.size() - index < s.size() - i)) {
                return false;
            }
        }*/

        //return true;
        
        if (s.empty()) {
            return true;
        }

        int si = 0;
        int ti = 0;

        for (int i = 0; i < t.size(); ++i) {

            if (t[i] == s[si]) {
                ++si;

                if (si == s.size()) {
                    return true;
                }
            }
        }

        return false;
    }
};