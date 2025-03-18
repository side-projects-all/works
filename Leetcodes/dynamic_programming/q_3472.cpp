/*
You are given a string s and an integer k.

In one operation, you can replace the character at any position with the next or previous letter in the alphabet (wrapping around so that 'a' is after 'z'). For example, replacing 'a' with the next letter results in 'b', and replacing 'a' with the previous letter results in 'z'. Similarly, replacing 'z' with the next letter results in 'a', and replacing 'z' with the previous letter results in 'y'.

Return the length of the longest

of s that can be obtained after performing at most k operations.

 

Example 1:

Input: s = "abced", k = 2

Output: 3

Explanation:

    Replace s[1] with the next letter, and s becomes "acced".
    Replace s[4] with the previous letter, and s becomes "accec".

The subsequence "ccc" forms a palindrome of length 3, which is the maximum.

Example 2:

Input: s = "aaazzz", k = 4

Output: 6

Explanation:

    Replace s[0] with the previous letter, and s becomes "zaazzz".
    Replace s[4] with the next letter, and s becomes "zaazaz".
    Replace s[3] with the next letter, and s becomes "zaaaaz".

The entire string forms a palindrome of length 6.

 

Constraints:

    1 <= s.length <= 200
    1 <= k <= 200
    s consists of only lowercase English letters.

*/

class Solution {
private:
    int by_iterative_dp(string& s, int& k) {
        int n = s.size();
        if (n == 1) {
            return 1;
        }

        std::vector<std::vector<std::vector<int>>> dp(n, std::vector<std::vector<int>>(n, std::vector<int>(k + 1, 0)));

        for (int i = 0; i < n; i++) {
            for (int c = 0; c <= k; c++) {
                dp[i][i][c] = 1;
            }
        }

        for (int b = n - 2; b >= 0; --b) { 
            for (int e = b + 1; e < n; ++e) {

                for (int c = 0; c <= k; ++c) {
                    if (s[b] == s[e]) {
                        dp[b][e][c] = dp[b + 1][e - 1][c] + 2;
                        
                    } else {
                        
                        int diff = std::abs(s[b] - s[e]);
                        diff = std::min(diff, 26 - diff);

                        dp[b][e][c] = std::max(dp[b + 1][e][c], dp[b][e - 1][c]);
                        if (c >= diff) {
                            dp[b][e][c] = std::max(dp[b][e][c], 2 + dp[b + 1][e - 1][c - diff]);
                        }
                    }
                }
            }
        }

        return dp[0][n-1][k];
    }
public:
    int longestPalindromicSubsequence(string s, int k) {
        return by_iterative_dp(s, k);
    }
};