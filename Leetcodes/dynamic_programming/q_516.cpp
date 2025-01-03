/*
Given a string s, find the longest palindromic subsequence's length in s.

A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.

 

Example 1:

Input: s = "bbbab"
Output: 4
Explanation: One possible longest palindromic subsequence is "bbbb".

Example 2:

Input: s = "cbbd"
Output: 2
Explanation: One possible longest palindromic subsequence is "bb".

 

Constraints:

    1 <= s.length <= 1000
    s consists only of lowercase English letters.


*/

class Solution {
private:
    int iterative(std::string& s) {
        int N = s.size();
        std::vector<std::vector<int>> mem(N, std::vector<int>(N));

        for (int r = N - 1; r >= 0; --r) {
            mem[r][r] = 1;

            for (int c = r + 1; c < N; ++c) {
                if (s[r] == s[c]) {
                    mem[r][c] = mem[r + 1][c - 1] + 2;
                } else {
                    mem[r][c] = std::max(mem[r + 1][c], mem[r][c - 1]);
                }
            }
        }

        return mem[0][N -1];
    }
    int recursive(std::string& s, int begin, int end, std::vector<std::vector<int>>& mem) {
        if (begin > end) {
            return 0;
        }

        if (begin == end) {
            return 1;
        }

        if (mem[begin][end] != -1) {
            return mem[begin][end];
        }

        if (s[begin] == s[end]) {
            mem[begin][end] = recursive(s, begin + 1, end - 1, mem) + 2;
        } else {
            mem[begin][end] = std::max(recursive(s, begin, end - 1, mem), recursive(s, begin + 1, end, mem));
        }

        return mem[begin][end];
    }

public:
    int longestPalindromeSubseq(string s) {
        //std::vector<std::vector<int>> mem(s.size(), std::vector<int>(s.size(), -1));

        //return recursive(s, 0, s.size() - 1, mem);
        return iterative(s);
    }
};