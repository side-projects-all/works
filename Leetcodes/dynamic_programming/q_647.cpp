/*
Given a string s, return the number of palindromic substrings in it.

A string is a palindrome when it reads the same backward as forward.

A substring is a contiguous sequence of characters within the string.

 

Example 1:

Input: s = "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".

Example 2:

Input: s = "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".

 

Constraints:

    1 <= s.length <= 1000
    s consists of lowercase English letters.


*/

class Solution {
private:
    int byPossibleCenters(string& s) {
        int N = s.size();
        
        if (N == 0) {
            return 0;
        }

        int ans = 0;

        std::function<int(int, int)> cnt = [&](int lo, int hi) -> int {
            int result = 0;

            while (lo >= 0 && hi < N) {
                if (s[lo] != s[hi]) {
                    break;
                }

                --lo;
                ++hi;
                ++result;
            }

            return result;
        };

        for (int i = 0; i < N; ++i) {
            ans += cnt(i, i);
            ans += cnt(i, i + 1);
        }

        return ans;
    }

    int byDP(string& s) {
        int N = s.size();
        int ans = N;

        if (N == 0) {
            return 0;
        }

        bool mem[N][N];
        std::fill_n(*mem, N * N, false);

        //base case: single character
        for (int i = 0; i < N; ++i) {
            mem[i][i] = true;
        }

        //base case: double character
        for (int i = 0; i < N - 1; ++i) {
            mem[i][i + 1] = (s[i] == s[i + 1]);

            ans += mem[i][i + 1];
        }

        for (int len = 3; len <= N; ++len) {

            //a sliding window moving
            for (int i = 0, j = i + len - 1; j < N; ++i, ++j) {
                mem[i][j] = mem[i + 1][j - 1] && (s[i] == s[j]);
                ans += mem[i][j];
            }
        }

        return ans;
    }
public:
    int countSubstrings(string s) {
        //return byDP(s);
        return byPossibleCenters(s);
    }
};