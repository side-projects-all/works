/*

*/

class Solution {
private:
    int iterative(vector<int>& rods) {
        std::unordered_map<int, int> dp;
        dp[0] = 0;

        for (int r : rods) {
            std::unordered_map<int, int> new_dp(dp);

            for (auto& p : dp) {
                int diff = p.first;
                int taller = p.second;
                int shorter = taller - diff;

                int newTaller = new_dp.find(diff + r) != new_dp.end() ? new_dp[diff + r] : 0;
                new_dp[diff + r] = std::max(newTaller, taller + r);

                int newDiff = std::abs(shorter + r - taller);
                int newTaller2 = std::max(shorter + r, taller);
                int val = new_dp.find(newDiff) != new_dp.end() ? new_dp[newDiff] : 0;
                new_dp[newDiff] = std::max(newTaller2, val);

            }

            dp = new_dp;
        }

        return dp.find(0) != dp.end() ? dp[0] : 0;
    }
public:
    int tallestBillboard(vector<int>& rods) {
        return iterative(rods);
    }
};