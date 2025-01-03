/*
Given a string s, encode the string such that its encoded length is the shortest.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. k should be a positive integer.

If an encoding process does not make the string shorter, then do not encode it. If there are several solutions, return any of them.

 

Example 1:

Input: s = "aaa"
Output: "aaa"
Explanation: There is no way to encode it such that it is shorter than the input string, so we do not encode it.

Example 2:

Input: s = "aaaaa"
Output: "5[a]"
Explanation: "5[a]" is shorter than "aaaaa" by 1 character.

Example 3:

Input: s = "aaaaaaaaaa"
Output: "10[a]"
Explanation: "a9[a]" or "9[a]a" are also valid solutions, both of them have the same length = 5, which is the same as "10[a]".

 

Constraints:

    1 <= s.length <= 150
    s consists of only lowercase English letters.


*/

class Solution {
public:
    // Helper function to check if a substring is a repeated version of a smaller substring
    bool isRepeat(const string& s, int i, int j, int k) {
        int len = j - i + 1;
        
        //need to divisible by k
        if (len % k != 0) {
            return false;
        }
        
        //compare with previous substring
        for (int m = i + k; m <= j; ++m) {
            if (s[m] != s[m - k]) {
                return false;
            }
        }
        return true;
    }

    string encode(string s) {
        int n = s.size();
        // DP table to store the shortest encoding of substring s[i:j+1]
        std::vector<std::vector<std::string>> dp(n, std::vector<std::string>(n, ""));
        
        // Iterate over all possible lengths of substrings
        for (int l = 0; l < n; ++l) {
            for (int i = 0; i + l < n; ++i) {
                int j = i + l;
                std::string sub_str = s.substr(i, l + 1);
                dp[i][j] = sub_str;  // Initialize the DP table with the substring itself

                // Try to split the substring into two parts and concatenate the encodings
                for (int k = i; k < j; ++k) {
                    if (dp[i][k].size() + dp[k + 1][j].size() < dp[i][j].size()) {
                        dp[i][j] = dp[i][k] + dp[k + 1][j];
                    }
                }

                // Check for repeating patterns in the current substring
                for (int k = 1; k <= (l + 1) / 2; ++k) {
                    if (isRepeat(s, i, j, k)) {
                        string encoded_str = std::to_string((l + 1) / k) + "[" + dp[i][i + k - 1] + "]";
                        if (encoded_str.size() < dp[i][j].size()) {
                            dp[i][j] = encoded_str;
                        }
                    }
                }
            }
        }
        
        // Return the shortest encoding for the entire string s[0:n-1]
        return dp[0][n - 1];
    }
};
