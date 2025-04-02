/*
Given a string s, partition s such that every
substring
of the partition is a
palindrome
. Return all possible palindrome partitioning of s.

 

Example 1:

Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Example 2:

Input: s = "a"
Output: [["a"]]

 

Constraints:

    1 <= s.length <= 16
    s contains only lowercase English letters.


*/

class Solution {
private:
    bool is_palindrome(std::string& s, int b, int e, std::vector<std::vector<int>>& dp) {
        if (dp[b][e] != -1) {
            return dp[b][e];
        }

        while (b < e) {
            if (s[b] != s[e]) {
                return dp[b][e] = false;
            }

            ++b;
            --e;
        }

        return dp[b][e] = true;
    }
    void recursive(std::vector<std::vector<std::string>>& ans, std::string& s, std::vector<std::string>&& curr, int b, std::vector<std::vector<int>>& dp) {
        int n = s.size();
        if (b == n) {
            ans.push_back(curr);
            return;
        }

        for (int e = b; e < n; ++e) {
            if (is_palindrome(s, b, e, dp)) {
                curr.push_back(s.substr(b, e - b + 1));
                recursive(ans, s, std::move(curr), e + 1, dp);
                curr.pop_back();
            }
        }    
    }
    vector<vector<string>> by_recursive_dp(string& s) {
        int n = s.size();
        if (n == 1) {
            return {{s}};
        }

        std::vector<std::vector<int>> dp(n, std::vector<int>(n, -1));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = true;
        }
        for (int i = 1; i < n; ++i) {

            if (s[i - 1] == s[i]) {
                dp[i - 1][i] = true;
            }
        }

        std::vector<std::vector<std::string>> ans;
        recursive(ans, s, std::vector<std::string>(), 0, dp);

        return ans;
    }
public:
    vector<vector<string>> partition(string s) {
        return by_recursive_dp(s);
    }
};