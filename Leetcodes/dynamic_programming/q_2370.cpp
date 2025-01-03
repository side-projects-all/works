/*
You are given a string s consisting of lowercase letters and an integer k. We call a string t ideal if the following conditions are satisfied:

    t is a subsequence of the string s.
    The absolute difference in the alphabet order of every two adjacent letters in t is less than or equal to k.

Return the length of the longest ideal string.

A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.

Note that the alphabet order is not cyclic. For example, the absolute difference in the alphabet order of 'a' and 'z' is 25, not 1.

 

Example 1:

Input: s = "acfgbd", k = 2
Output: 4
Explanation: The longest ideal string is "acbd". The length of this string is 4, so 4 is returned.
Note that "acfgbd" is not ideal because 'c' and 'f' have a difference of 3 in alphabet order.

Example 2:

Input: s = "abcd", k = 3
Output: 4
Explanation: The longest ideal string is "abcd". The length of this string is 4, so 4 is returned.

 

Constraints:

    1 <= s.length <= 10^5
    0 <= k <= 25
    s consists of lowercase English letters.


*/

class Solution {
private:
    int iterative(string& s, int k) {
        int N = s.size();
        std::vector<int> mem(26);

        int ans = 0;
        for (int i = 0; i < N; ++i) {
            int curr = s[i] - 'a';
            int best = 0;

            for (int prev = 0; prev < 26; ++prev) {
                if (std::abs(prev - curr) <= k) {
                    best = std::max(best, mem[prev]);
                }
            }

            mem[curr] = std::max(mem[curr], best + 1);
            ans = std::max(ans, mem[curr]);
        }
        
        return ans;
    }
    int recursive(string& s, int k) {
        int N = s.size();
        std::vector<std::vector<int>> mem(N, std::vector<int>(26, -1));

        std::function<int(int, int)> rec = [&](int i, int c) -> int {
            if (mem[i][c] != -1) {
                return mem[i][c];
            }

            mem[i][c] = 0;
            bool match = (c == (s[i] - 'a'));
            if (match) {
                mem[i][c] = 1;
            }

            if (i > 0) {
                mem[i][c] = rec(i - 1, c);

                if (match) {
                    for (int p = 0; p < 26; ++p) {
                        if (std::abs(c - p) <= k) {
                            mem[i][c] = std::max(mem[i][c], rec(i - 1, p) + 1);
                        }
                    }
                }
            }

            return mem[i][c];
        };

        int ans = -1;
        for (int c = 0; c < 26; ++c) {
            ans = std::max(ans, rec(N - 1, c));
        }

        return ans;
    }
public:
    int longestIdealString(string s, int k) {
        //return recursive(s, k);
        return iterative(s, k);
    }
};