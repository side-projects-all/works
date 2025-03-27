/*
We can scramble a string s to get a string t using the following algorithm:

    If the length of the string is 1, stop.
    If the length of the string is > 1, do the following:
        Split the string into two non-empty substrings at a random index, i.e., if the string is s, divide it to x and y where s = x + y.
        Randomly decide to swap the two substrings or to keep them in the same order. i.e., after this step, s may become s = x + y or s = y + x.
        Apply step 1 recursively on each of the two substrings x and y.

Given two strings s1 and s2 of the same length, return true if s2 is a scrambled string of s1, otherwise, return false.

 

Example 1:

Input: s1 = "great", s2 = "rgeat"
Output: true
Explanation: One possible scenario applied on s1 is:
"great" --> "gr/eat" // divide at random index.
"gr/eat" --> "gr/eat" // random decision is not to swap the two substrings and keep them in order.
"gr/eat" --> "g/r / e/at" // apply the same algorithm recursively on both substrings. divide at random index each of them.
"g/r / e/at" --> "r/g / e/at" // random decision was to swap the first substring and to keep the second substring in the same order.
"r/g / e/at" --> "r/g / e/ a/t" // again apply the algorithm recursively, divide "at" to "a/t".
"r/g / e/ a/t" --> "r/g / e/ a/t" // random decision is to keep both substrings in the same order.
The algorithm stops now, and the result string is "rgeat" which is s2.
As one possible scenario led s1 to be scrambled to s2, we return true.

Example 2:

Input: s1 = "abcde", s2 = "caebd"
Output: false

Example 3:

Input: s1 = "a", s2 = "a"
Output: true

 

Constraints:

    s1.length == s2.length
    1 <= s1.length <= 30
    s1 and s2 consist of lowercase English letters.


*/

class Solution {
private:
    bool recursive(string& s1, int i1, string& s2, int i2, std::vector<std::vector<std::vector<int>>>& mem, int len) {
        if (len == 1) {
            return s1[i1] == s2[i2];
        }

        if (mem[len][i1][i2] != -1) {
            return mem[len][i1][i2];
        }

        for (int cut_at = 1; cut_at < len; ++cut_at) {
            
            int not_swap = recursive(s1, i1, s2, i2, mem, cut_at) && recursive(s1, i1 + cut_at, s2, i2 + cut_at, mem, len - cut_at);
            int swap = recursive(s1, i1, s2, len + i2 - cut_at, mem, cut_at) && recursive(s1, i1 + cut_at, s2, i2, mem, len - cut_at);
            if (not_swap || swap) {
                return mem[len][i1][i2] = true;
            }
        }

        return mem[len][i1][i2] = false;
    }
    bool by_recursive_dp(string& s1, string& s2) {
        int n = s1.size();
        std::vector<std::vector<std::vector<int>>> mem(n + 1, std::vector<std::vector<int>>(n, std::vector<int>(n, -1)));

        return recursive(s1, 0, s2, 0, mem, n);
    }
    bool by_iterative_dp(string& s1, string& s2) {
        int n = s1.size();
        std::vector<std::vector<std::vector<int>>> dp(n + 1, std::vector<std::vector<int>>(n, std::vector<int>(n)));

        for (int i1 = 0; i1 < n; ++i1) {
            for (int i2 = 0; i2 < n; ++i2) {
                dp[1][i1][i2] = s1[i1] == s2[i2];
            }
        }

        for (int len = 2; len <= n; ++len) {
            for (int i1 = 0; i1 <= n - len; ++i1) {
                for (int i2 = 0; i2 <= n - len; ++i2) {
                    
                    for (int cut_at = 1; cut_at < len; ++cut_at) {
                        //not swap
                        dp[len][i1][i2] |= (dp[cut_at][i1][i2] && dp[len - cut_at][i1 + cut_at][i2 + cut_at]);
                        //swap 
                        dp[len][i1][i2] |= (dp[cut_at][i1][len - cut_at + i2] && dp[len - cut_at][i1 + cut_at][i2]);
                    }
                }
            }
        }

        return dp[n][0][0];
    }
public:
    bool isScramble(string s1, string s2) {
        //return by_iterative_dp(s1, s2);
        return by_recursive_dp(s1, s2);
    }
};