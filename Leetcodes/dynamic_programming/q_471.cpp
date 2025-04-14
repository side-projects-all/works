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
private:
    //check if a substring is a repeated version of a smaller substring
    bool is_repeat(std::string& s, int i, int j, int k) {
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
    std::string by_iterative_dp(std::string& s) {
        int n = s.size();
        if (n <= 4) {
            return s;
        }

        //store shortest encoded string between i, j
        std::vector<std::vector<std::string>> dp(n, std::vector<std::string>(n));   

        //all possible lengths of substrings
        for (int len = 0; len < n; ++len) {
            for (int i = 0; i < n - len; ++i) {
                int j = i + len;
                std::string sub = s.substr(i, len + 1);
                dp[i][j] = sub;     //init the DP table with the substring itself

                //adjust shortest encoded string, split the substring into two parts and concatenate the encodings
                for (int k = i; k < j; ++k) {
                    if (dp[i][k].size() + dp[k + 1][j].size() < dp[i][j].size()) {
                        dp[i][j] = dp[i][k] + dp[k + 1][j];
                    }
                }

                //check if repeated
                for (int k = 1; k <= (len + 1) / 2; ++k) {  //(len + 1) / 2 for decimal part removed situation
                    if (is_repeat(s, i, j, k)) {
                        std::string encoded = std::to_string((len + 1) / k) + "[" + dp[i][i + k - 1] + "]";

                        if (encoded.size() < dp[i][j].size()) {
                            dp[i][j] = encoded;
                        }
                    }
                }
            }
        }

        return dp[0][n - 1];
    }
public:
    string encode(string s) {
        return by_iterative_dp(s);
    }
};
