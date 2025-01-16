/*
Given a string s, find the longest palindromic subsequence's length in s.

A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.

 

Example 1:

Input: s = "bbbab"
Output: 4
Explanation: One possible longest palindromic subsequence is "bbbb".

Example 2:

Input: s = "cbbd"
Output: 2
Explanation: One possible longest palindromic subsequence is "bb".

 

Constraints:

    1 <= s.length <= 1000
    s consists only of lowercase English letters.


*/

class Solution {
private:
    int iterative(std::string& s) {
        int n = s.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(n));

        for (int b = n - 1; b >= 0; --b) {
            dp[b][b] = 1;

            for (int e = b + 1; e < n; ++e) {

                if (s[b] == s[e]) {
                    dp[b][e] = 2 + dp[b + 1][e - 1];

                } else {
                    dp[b][e] = std::max(dp[b + 1][e], dp[b][e - 1]);
                }

            }
        }

        return dp[0][n - 1];
    }
    int recursive(std::string& s, std::vector<std::vector<int>>& mem, int b, int e) {
        if (b > e) {
            return 0;
        }

        if (b == e) {
            return 1;
        }

        if (mem[b][e] != -1) {
            return mem[b][e];
        }

        if (s[b] == s[e]) {
            return mem[b][e] = recursive(s, mem, b + 1, e - 1) + 2;
        }

        return mem[b][e] = std::max(recursive(s, mem, b + 1, e), recursive(s, mem, b, e - 1));
    }

    int by_recursive_dp(std::string& s) {
        int n = s.size();
        std::vector<std::vector<int>> mem(n, std::vector<int>(n, - 1));

        return recursive(s, mem, 0, n - 1);
    }

public:
    int longestPalindromeSubseq(string s) {
        if (s.size() == 1) {
            return 1;
        }

        //return by_recursive_dp(s);
        return iterative(s);
    }
};