/*
Given a string s. In one step you can insert any character at any index of the string.

Return the minimum number of steps to make s palindrome.

A Palindrome String is one that reads the same backward as well as forward.

 

Example 1:

Input: s = "zzazz"
Output: 0
Explanation: The string "zzazz" is already palindrome we do not need any insertions.

Example 2:

Input: s = "mbadm"
Output: 2
Explanation: String can be "mbdadbm" or "mdbabdm".

Example 3:

Input: s = "leetcode"
Output: 5
Explanation: Inserting 5 characters the string becomes "leetcodocteel".

 

Constraints:

    1 <= s.length <= 500
    s consists of lowercase English letters.



*/

class Solution {
private:
    int by_iterative_dp(string& s) {
        int n = s.size();
        if (n == 1) {
            return 0;
        }

        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1));
        std::string rev = s;
        std::reverse(rev.begin(), rev.end());

        for (int b = 1; b <= n; ++b) {
            for (int rb = 1; rb <= n; ++rb) {
                if (s[b - 1] == rev[rb - 1]) {
                    dp[b][rb] = 1 + dp[b - 1][rb - 1];

                } else {
                    dp[b][rb] = std::max(dp[b - 1][rb], dp[b][rb - 1]);
                }
            }
        }

        return n - dp[n][n];
    }

    /*
    int another_recursive(std::string& s, int left, int right, std::vector<std::vector<int>>& mem) {
        if (left >= right) {
            return 0;
        }

        if (mem[left][right] != -1) {
            return mem[left][right];
        }

        if (s[left] == s[right]) {
            mem[left][right] = recursive(s, left + 1, right - 1, mem);
        } else {
            //the plus 1 here means you meet difference and need to insert one to create palindrome, 
            //then you need to continue to find common substring
            mem[left][right] = 1 + std::min(recursive(s, left + 1, right, mem), 
                                        recursive(s, left, right - 1, mem));
        }

        return mem[left][right];
    }
    */

    int recursive(std::string& s, std::string& rev, std::vector<std::vector<int>>& mem, int len_s, int len_rev) {
        if (len_s == 0 || len_rev == 0) {
            return 0;
        }

        if (mem[len_s][len_rev] != -1) {
            return mem[len_s][len_rev];
        }

        if (s[len_s - 1] == rev[len_rev - 1]) {
            return mem[len_s][len_rev] = 1 + recursive(s, rev, mem, len_s - 1, len_rev - 1);
        }

        return mem[len_s][len_rev] = std::max(recursive(s, rev, mem, len_s - 1, len_rev), 
                                                recursive(s, rev, mem, len_s, len_rev - 1));
    }

    int by_recursive_dp(string& s) {
        //std::vector<std::vector<int>> mem(s.size(), std::vector<int>(s.size(), -1));

        //return another_recursive(s, 0, s.size() - 1, mem);
        int n = s.size();
        std::vector<std::vector<int>> mem(n + 1, std::vector<int>(n + 1, -1));
        std::string rev = s;
        std::reverse(rev.begin(), rev.end());

        recursive(s, rev, mem, n, n);

        return n - mem[n][n];
    }
public:
    int minInsertions(string s) {
        return by_recursive_dp(s);
        //return by_iterative_dp(s);
    }
};
