/*
You are given an integer array nums and an integer target.

You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.

    For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".

Return the number of different expressions that you can build, which evaluates to target.

 

Example 1:

Input: nums = [1,1,1,1,1], target = 3
Output: 5
Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3

Example 2:

Input: nums = [1], target = 1
Output: 1

 

Constraints:

    1 <= nums.length <= 20
    0 <= nums[i] <= 1000
    0 <= sum(nums[i]) <= 1000
    -1000 <= target <= 1000


*/

class Solution {
private:
    int by_dp(vector<int>& nums, int& target) {
        int n = nums.size();
        if (n == 1) {

            if (nums[0] == 0) {
                return 2;
            }
            
            return nums[0] == std::abs(target);
        }

        int total = std::accumulate(nums.begin(), nums.end(), 0);
        if (std::abs(target) > total) {
            return 0;
        }

        std::vector<std::vector<int>> dp(n, std::vector<int>(2 * total + 1));
        dp[0][total + nums[0]] = 1;
        dp[0][total - nums[0]] += 1;    //+ for nums[0] is zero!
        for (int i = 1; i < n; ++i) {
            for (int sum = -total; sum <= total; ++sum) {

                if (dp[i - 1][total + sum] > 0) {
                    dp[i][sum + total - nums[i]] += dp[i - 1][total + sum];
                    dp[i][sum + total + nums[i]] += dp[i - 1][total + sum];
                }
            }
        }

        return dp[n - 1][target + total];
    }
    int recursive(vector<int>& nums, vector<vector<int>>& mem, int& target, int& total, int curr_i, int curr_sum) {
        if (curr_i == nums.size()) {

            if (curr_sum == target) {
                return 1;
            }

            return 0;
        }

        if (mem[curr_i][curr_sum + total] != INT_MIN) {
            return mem[curr_i][curr_sum + total];
        }

        int inc = recursive(nums, mem, target, total, curr_i + 1, curr_sum + nums[curr_i]);
        int decr = recursive(nums, mem, target, total, curr_i + 1, curr_sum - nums[curr_i]);

        return mem[curr_i][curr_sum + total] = inc + decr;
    }

    int by_recursive(vector<int>& nums, int& target) {
        int total = std::accumulate(nums.begin(), nums.end(), 0);
        std::vector<std::vector<int>> mem(nums.size(), std::vector<int>(2 * total + 1, INT_MIN));

        return recursive(nums, mem, target, total, 0, 0);
    }
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        //return by_recursive(nums, target);
        return by_dp(nums, target);
    }
};