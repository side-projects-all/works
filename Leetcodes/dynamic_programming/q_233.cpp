/*
Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.

 

Example 1:

Input: n = 13
Output: 6

Example 2:

Input: n = 0
Output: 0

 

Constraints:

    0 <= n <= 10^9


*/

class Solution {
private:
    int by_iterative_dp(int& n) {
        if (n <= 9) {
            return n != 0;
        }

        std::string s = std::to_string(n);
        int len = s.size();
        std::vector<std::vector<std::vector<unsigned int>>> dp(len + 1, std::vector<std::vector<unsigned int>>(len + 1, std::vector<unsigned int>(2)));

        //base cases
        for (int cnt1 = 0; cnt1 <= len; ++cnt1) {
            dp[len][cnt1][0] = cnt1;
            dp[len][cnt1][1] = cnt1;
        }

        for (int pos = len - 1; pos >= 0; --pos) {
            for (int cnt1 = 0; cnt1 <= pos; ++cnt1) {
                for (int tight = 0; tight <= 1; ++tight) {

                    int max_digit = tight ? (s[pos] - '0') : 9;

                    for (int d = 0; d <= max_digit; ++d) {
                        dp[pos][cnt1][tight] += dp[pos + 1][cnt1 + (d == 1)][tight && (d == max_digit)];
                    }
                }
            }
        }

        return dp[0][0][1];
    }
    int by_math(int& n) {
        if (n <= 9) {
            return n != 0;
        }

        int cnt = 0;
        for (long long i = 1; i <= n; i *= 10) {
            long long divider = i * 10;
            cnt += (n / divider) * i + std::min(std::max(n % divider - i + 1, 0LL), i);
        }

        return cnt;
    }
    int recursive(std::string& s, std::vector<std::vector<std::vector<int>>>& mem, int pos, int cnt1, int limit) {
        if (pos == s.size()) {
            return cnt1;
        }

        if (mem[pos][cnt1][limit] != -1) {
            return mem[pos][cnt1][limit];
        }

        int max_digit = limit ? s[pos] - '0' : 9;
        int cnt_ans = 0;

        for (int d = 0; d <= max_digit; ++d) {
            cnt_ans += recursive(s, mem, pos + 1, cnt1 + (d == 1), limit && d == max_digit);
        }

        return mem[pos][cnt1][limit] = cnt_ans;
    }
    int by_recursive_dp(int& n) {
        if (n <= 9) {
            return n != 0;
        }

        std::string s = std::to_string(n);
        int len = s.size();
        std::vector<std::vector<std::vector<int>>> mem(len + 1, std::vector<std::vector<int>>(len + 1, std::vector<int>(2, - 1)));

        int ans = recursive(s, mem, 0, 0, 1);
        return ans;
    }
public:
    int countDigitOne(int n) {
        return by_iterative_dp(n);
        //return by_recursive_dp(n);
        //return by_math(n);
    }
};