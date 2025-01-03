/*
Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

    For example, "ace" is a subsequence of "abcde".

A common subsequence of two strings is a subsequence that is common to both strings.

 

Example 1:

Input: text1 = "abcde", text2 = "ace" 
Output: 3  
Explanation: The longest common subsequence is "ace" and its length is 3.

Example 2:

Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.

Example 3:

Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.

 

Constraints:

    1 <= text1.length, text2.length <= 1000
    text1 and text2 consist of only lowercase English characters.


*/

class Solution {
private:
    int iterative_optimize(string& text1, string& text2) {
        int N1 = text1.size();
        int N2 = text2.size();

        if (N1 > N2) {
            return iterative_optimize(text2, text1);
        }
        std::vector<int> pre(N1 + 1);
        std::vector<int> curr(N1 + 1);

        for (int c = N2 - 1; c > -1; --c) {

            std::fill(curr.begin(), curr.end(), 0);
            for (int r = N1 - 1; r > -1; --r) {
                if (text1[r] == text2[c]) {
                    curr[r] = 1 + pre[r + 1];
                } else {
                    curr[r] = std::max(pre[r], curr[r + 1]);
                }
            }

            pre = curr;
        }

        return pre[0];
    }
    
    int iterative(std::string& text1, std::string& text2) {
        std::vector<std::vector<int>> mem(text1.size() + 1, std::vector<int>(text2.size() + 1, 0));
        int n01 = text1.size();
        int n02 = text2.size();

        for (int t1 = text1.size() - 1; t1 > -1 ; --t1) {
            for (int t2 = text2.size() - 1; t2 > -1; --t2) {

                if (text1[t1] == text2[t2]) {
                    mem[t1][t2] = 1 + mem[t1 + 1][t2 + 1];
                } else {
                    mem[t1][t2] = std::max(mem[t1 + 1][t2], mem[t1][t2 + 1]);
                }
            }
        }

        return mem[0][0];
    }

    int recursive(std::string& text1, std::string& text2, 
                    int idx01, int idx02, std::vector<std::vector<int>>& mem) {

        if (idx01 == text1.size() || idx02 == text2.size()) {
            return 0;
        }

        if (mem[idx01][idx02] != -1) {
            return mem[idx01][idx02];
        }

        int len = 0;
        if (text1[idx01] == text2[idx02]) {
            len = 1 + recursive(text1, text2, idx01 + 1, idx02 + 1, mem);
        } else {
            len = std::max(recursive(text1, text2, idx01 + 1, idx02, mem), 
                            recursive(text1, text2, idx01, idx02 + 1, mem));
        }

        mem[idx01][idx02] = len;

        return len;
    }
public:
    int longestCommonSubsequence(string text1, string text2) {
        //std::vector<std::vector<int>> mem(text1.size(), std::vector<int>(text2.size(), -1));
        
        //return recursive(text1, text2, 0, 0, mem);
        return iterative(text1, text2);
    }
};