/*
Given a string s, return the length of the longest repeating substrings. If no repeating substring exists, return 0.

 

Example 1:

Input: s = "abcd"
Output: 0
Explanation: There is no repeating substring.

Example 2:

Input: s = "abbaba"
Output: 2
Explanation: The longest repeating substrings are "ab" and "ba", each of which occurs twice.

Example 3:

Input: s = "aabcaabdaab"
Output: 3
Explanation: The longest repeating substring is "aab", which occurs 3 times.

 

Constraints:

    1 <= s.length <= 2000
    s consists of lowercase English letters.


*/

class Solution {
public:
    int longestRepeatingSubstring(string s) {
        int n = s.size();
        int max_len = 0;
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1));

        for (int i = 1; i <= n; ++i) {          // i means the substring length
            for (int j = i + 1; j <= n; ++j) {  // j means the last cahr of another substring now
                if (s[i - 1] == s[j - 1]) {         //if their previous positions had the same char, 
                    dp[i][j] = dp[i - 1][j - 1] + 1;        //you add 1 from pre-recorded LRS
                    max_len = std::max(max_len, dp[i][j]);
                }
            }
        }

        return max_len;
    }
};
