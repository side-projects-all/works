/*
You are given two strings, s and t.

You can create a new string by selecting a

from s (possibly empty) and a substring from t (possibly empty), then concatenating them in order.

Return the length of the longest

that can be formed this way.

 

Example 1:

Input: s = "a", t = "a"

Output: 2

Explanation:

Concatenating "a" from s and "a" from t results in "aa", which is a palindrome of length 2.

Example 2:

Input: s = "abc", t = "def"

Output: 1

Explanation:

Since all characters are different, the longest palindrome is any single character, so the answer is 1.

Example 3:

Input: s = "b", t = "aaaa"

Output: 4

Explanation:

Selecting "aaaa" from t is the longest palindrome, so the answer is 4.

Example 4:

Input: s = "abcde", t = "ecdba"

Output: 5

Explanation:

Concatenating "abc" from s and "ba" from t results in "abcba", which is a palindrome of length 5.

 

Constraints:

    1 <= s.length, t.length <= 1000
    s and t consist of lowercase English letters.

*/


class Solution {
private:
    int by_iterative_dp(string& s, string& t) {
        int n = s.size();
        int m = t.size();

        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));   //longest palindrome between two indices

        int ans = 0;
        for (int i = 0; i < n; i++) {           //from begin of s
            for (int j = m - 1; j >= 0; j--) {  //from end of t, treat two strings as a string

                if (s[i] == t[j]) {
                    if (i == 0 || j == m - 1) {
                        dp[i][j] = 2;
                    } else {
                        dp[i][j] = dp[i - 1][j + 1] + 2;
                    }
                } else {
                    dp[i][j] = 0;
                }
                
                ans = std::max(ans, dp[i][j]);
            }
        }

        // odd
        for (int i = 0; i < n; i++) {
            int l = i, r = i;
            while (0 <= l && r < n && s[l] == s[r]) {
                l--; r++;
            }

            if (l < 0) {
                ans = std::max(ans, r - l - 1);
            } else {
                for (int j = 0; j < m; j++) {
                    ans = std::max(ans, r - l - 1 + dp[l][j]);
                }
            }
        }
        for (int i = 0; i < m; i++) {
            int l = i, r = i;
            while (0 <= l && r < m && t[l] == t[r]) {
                l--; r++;
            }

            if (r > m - 1) {
                ans = std::max(ans, r - l - 1);
            } else {
                for (int j = 0; j < n; j++) {
                    ans = std::max(ans, r - l - 1 + dp[j][r]);
                }
            }
        }

        // even
        for (int i = 0; i < n - 1; i++) {
            int l = i, r = i + 1;
            while (0 <= l && r < n && s[l] == s[r]) {
                l--; r++;
            }

            if (l < 0) {
                ans = std::max(ans, r - l - 1);
            } else {
                for (int j = 0; j < m; j++) {
                    ans = std::max(ans, r - l - 1 + dp[l][j]);
                }
            }
        }
        for (int i = 0; i < m - 1; i++) {
            int l = i, r = i + 1;
            while (0 <= l && r < m && t[l] == t[r]) {
                l--; r++;
            }

            if (r > m - 1) {
                ans = std::max(ans, r - l - 1);
            } else {
                for (int j = 0; j < n; j++) {
                    ans = std::max(ans, r - l - 1 + dp[j][r]);
                }
            }
        }

        return ans;
    }
public:
    int longestPalindrome(string s, string t) {
        return by_iterative_dp(s, t);
    }
};