#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

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
public:
    Solution() {}
    ~Solution() {}

    int countDigitOne(int n) {
        return by_iterative_dp(n);
    }
};