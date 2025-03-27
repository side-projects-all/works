/*
Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.

An interleaving of two strings s and t is a configuration where s and t are divided into n and m non-empty substrings respectively, such that:

    s = s1 + s2 + ... + sn
    t = t1 + t2 + ... + tm
    |n - m| <= 1
    The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...

Note: a + b is the concatenation of strings a and b.

 

Example 1:

Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true
Explanation: One way to obtain s3 is:
Split s1 into s1 = "aa" + "bc" + "c", and s2 into s2 = "dbbc" + "a".
Interleaving the two splits, we get "aa" + "dbbc" + "bc" + "a" + "c" = "aadbbcbcac".
Since s3 can be obtained by interleaving s1 and s2, we return true.

Example 2:

Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false
Explanation: Notice how it is impossible to interleave s2 with any other string to obtain s3.

Example 3:

Input: s1 = "", s2 = "", s3 = ""
Output: true

 

Constraints:

    0 <= s1.length, s2.length <= 100
    0 <= s3.length <= 200
    s1, s2, and s3 consist of lowercase English letters.

*/

class Solution {
private:
    bool recursive(string& s1, string& s2, string& s3, std::vector<std::vector<int>>& mem, int i, int j, int k) {
        if (i == s1.size()) {
            return s2.substr(j) == s3.substr(k);
        }

        if (j == s2.size()) {
            return s1.substr(i) == s3.substr(k);
        }

        if (mem[i][j] != -1) {
            return mem[i][j];
        }

        if ((s3[k] == s1[i] && recursive(s1, s2, s3, mem, i + 1, j, k + 1)) || (s3[k] == s2[j] && recursive(s1, s2, s3, mem, i, j + 1, k + 1))) {
            return mem[i][j] = true;
        }

        return mem[i][j] = false;
    }
    bool by_recursive_dp(string& s1, string& s2, string& s3) {
        int n1 = s1.size();
        int n2 = s2.size();
        int n3 = s3.size();
        if (n1 + n2 != n3) {
            return false;
        }

        if (n1 == 0) {
            return s2 == s3;
        }

        if (n2 == 0) {
            return s1 == s3;
        }

        //n3 equal to n1 + n2, so it is the result of all combination 
        std::vector<std::vector<int>> mem(n1, std::vector<int>(n2, -1));


        return recursive(s1, s2, s3, mem, 0, 0, 0);
    }
    bool by_iterative_dp(string& s1, string& s2, string& s3) {
        int n1 = s1.size();
        int n2 = s2.size();
        int n3 = s3.size();
        if (n1 + n2 != n3) {
            return false;
        }

        //under the premise of n1 + n2 == n3!
        if (n1 == 0) {
            return s2 == s3;
        }

        if (n2 == 0) {
            return s1 == s3;
        }
        //n3 equal to n1 + n2, so it is the result of all combination 
        std::vector<std::vector<bool>> dp(n1 + 1, std::vector<bool>(n2 + 1));
        //all empty
        dp[0][0] = true;
        //n2 = 0
        for (int i = 1; i <= n1; ++i) {
            dp[i][0] = dp[i - 1][0] && s1[i - 1] == s3[i - 1];
        }

        //n1 = 0
        for (int i = 1; i <= n2; ++i) {
            dp[0][i] = dp[0][i - 1] && s2[i - 1] == s3[i - 1];
        }

        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
                dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) || (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }

        return dp[n1][n2];
    }
public:
    bool isInterleave(string s1, string s2, string s3) {
        //return by_iterative_dp(s1, s2, s3);
        
        return by_recursive_dp(s1, s2, s3);
    }
};