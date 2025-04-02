/*
Given a string s, partition s such that every
substring
of the partition is a
palindrome
.

Return the minimum cuts needed for a palindrome partitioning of s.

 

Example 1:

Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.

Example 2:

Input: s = "a"
Output: 0

Example 3:

Input: s = "ab"
Output: 1

 

Constraints:

    1 <= s.length <= 2000
    s consists of lowercase English letters only.


*/

class Solution {
private:
    void palindrome_min_cuts(string& s, std::vector<int>& dp, int b, int e) {
        int n = s.size();
        int min_cuts = 0;
        while (b >= 0 && e < n && s[b] == s[e]) {

            min_cuts = (b == 0) ? 0 : 1 + dp[b - 1];
            dp[e] = std::min(dp[e], min_cuts);

            --b;
            ++e;
        }
    }
    int from_possible_mid(string& s) {
        int n = s.size();
        if (n == 1) {
            return 0;
        }

        //maximal cuts at every index
        std::vector<int> dp(n);
        for (int i = 1; i < n; ++i) {
            dp[i] = i;
        }

        for (int i = 0; i < n; ++i) {
            palindrome_min_cuts(s, dp, i, i);
            palindrome_min_cuts(s, dp, i, i + 1);
        }

        return dp[n - 1];
    }
    int by_optimize_iterative_dp(string& s) {
        int n = s.size();
        if (n == 1) {
            return 0;
        }

        //for every combination of subsring in s, check if palindrome
        std::vector<std::vector<bool>> is_palindrome(n, std::vector<bool>(n));
        //cuts at every index
        std::vector<int> dp(n);
        for (int e = 0; e < n; ++e) {

            int min_cuts = e;
            for (int b = 0; b <= e; ++b) {
                if (s[b] == s[e] && (e - b <= 2 || is_palindrome[b + 1][e - 1])) {
                    is_palindrome[b][e] = true;

                    min_cuts = b == 0 ? 0 : std::min(min_cuts, 1 + dp[b - 1]);
                }
            }

            dp[e] = min_cuts;
        }

        return dp[n - 1];
    }
    int by_iterative_dp(string& s) {
        int n = s.size();
        if (n == 1) {
            return 0;
        }

        //for every combination of subsring in s, check if palindrome
        std::vector<std::vector<bool>> is_palindrome(n, std::vector<bool>(n));
        
        for (int i = 0; i < n; ++i) {
            is_palindrome[i][i] = true;
        }
        for (int i = 1; i < n; ++i) {
            if (s[i - 1] == s[i]) {
                is_palindrome[i - 1][i] = true;
            }
        }
        for (int e = 2; e < n; ++e) {
            for (int b = 0; b < e; ++b) {
                if (s[b] == s[e] && is_palindrome[b + 1][e - 1]) {
                    is_palindrome[b][e] = true;
                }
            }
        }

        std::vector<int> dp(n);
        for (int e = 1; e < n; ++e) {

            int min_cuts = e;
            for (int b = 0; b <= e; ++b) {
                if (is_palindrome[b][e]) {
                    min_cuts = (b == 0) ? 0 : std::min(min_cuts, 1 + dp[b - 1]);
                }
            }

            dp[e] = min_cuts;
        }

        return dp[n - 1];
    }
public:
    int minCut(string s) {
        //return by_iterative_dp(s);
        //return by_optimize_iterative_dp(s);
        return from_possible_mid(s);
    }
};