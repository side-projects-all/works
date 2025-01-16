/*
Given two strings s1 and s2, return the lowest ASCII sum of deleted characters to make two strings equal.

 

Example 1:

Input: s1 = "sea", s2 = "eat"
Output: 231
Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.

Example 2:

Input: s1 = "delete", s2 = "leet"
Output: 403
Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d] + 101[e] + 101[e] to the sum.
Deleting "e" from "leet" adds 101[e] to the sum.
At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.

 

Constraints:

    1 <= s1.length, s2.length <= 1000
    s1 and s2 consist of lowercase English letters.


*/

class Solution {
private:
    int iterative(string& s1, string& s2) {
        int len1 = s1.size();
        int len2 = s2.size();
        std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1));

        for (int i1 = 1; i1 <= len1; ++i1) {
            dp[i1][0] = s1[i1 - 1] + dp[i1 - 1][0];
        }

        for (int i2 = 1; i2 <= len2; ++i2) {
            dp[0][i2] = s2[i2 - 1] + dp[0][i2 - 1];
        }

        for (int i1 = 1; i1 <= len1; ++i1) {
            for (int i2 = 1; i2 <= len2; ++i2) {

                if (s1[i1 - 1] == s2[i2 - 1]) {
                    dp[i1][i2] = dp[i1 - 1][i2 - 1];

                } else {

                    dp[i1][i2] = std::min(s1[i1 - 1] + dp[i1 - 1][i2], s2[i2 - 1] + dp[i1][i2 - 1]);
                    /*
                    dp[i1][i2] = std::min({s1[i1 - 1] + s2[i2 - 1] + dp[i1 - 1][i2 - 1], 
                                            s1[i1 - 1] + dp[i1 - 1][i2], 
                                            s2[i2 - 1] + dp[i1][i2 - 1]});
                    */
                }
            }
        }

        return dp[len1][len2];
    }
    int recursive(string& s1, string& s2, std::vector<std::vector<int>>& mem, int i1, int i2) {
        if (i1 == s1.size() && i2 == s2.size()) {
            return 0;
        }

        if (i1 == s1.size()) {
            
            return mem[i1][i2] = s2[i2] + recursive(s1, s2, mem, i1, i2 + 1);;
        }

        if (i2 == s2.size()) {
            
            return mem[i1][i2] = s1[i1] + recursive(s1, s2, mem, i1 + 1, i2);;
        }

        if (mem[i1][i2] != -1) {
            return mem[i1][i2];
        }

        if (s1[i1] == s2[i2]) {
            return mem[i1][i2] = recursive(s1, s2, mem, i1 + 1, i2 + 1);

        }
        
        return mem[i1][i2] = std::min(s1[i1] + recursive(s1, s2, mem, i1 + 1, i2), 
                                        s2[i2] + recursive(s1, s2, mem, i1, i2 + 1));
        /*
        return mem[i1][i2] = std::min({s1[i1] + recursive(s1, s2, mem, i1 + 1, i2), 
                                        s2[i2] + recursive(s1, s2, mem, i1, i2 + 1), 
                                        s1[i1] + s2[i2] + recursive(s1, s2, mem, i1 + 1, i2 + 1)});
        */
    }
    int by_recursive_dp(string& s1, string& s2) {
        int len1 = s1.size();
        int len2 = s2.size();

        std::vector<std::vector<int>> mem(len1 + 1, std::vector<int>(len2 + 1, -1));

        return recursive(s1, s2, mem, 0, 0);
    }
public:
    int minimumDeleteSum(string s1, string s2) {
        return by_recursive_dp(s1, s2);
        //return iterative(s1, s2);
    }
};