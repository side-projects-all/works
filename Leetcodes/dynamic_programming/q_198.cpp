/*
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

 

Example 1:

Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.

Example 2:

Input: nums = [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
Total amount you can rob = 2 + 9 + 1 = 12.

 

Constraints:

    1 <= nums.length <= 100
    0 <= nums[i] <= 400


*/

class Solution {
private:
    int iterative2(std::vector<int>& nums) {
        /*
        int N = nums.size();
        int next = nums[N - 1];
        int nextPlusOne = 0;

        for (int i = N - 2; i > -1; --i) {
            int curr = std::max(next, nextPlusOne + nums[i]);

            nextPlusOne = next;
            next = curr;
        }

        return next;
        */
        
        /*
        int n = nums.size();
        if (n == 1) {
            return nums[0];
        }

        if (n == 2) {
            return std::max(nums[0], nums[1]);
        }

        std::vector<int> dp(n + 1); //this means how many houses
        dp[1] = nums[0];
        dp[2] = std::max(nums[0], nums[1]);

        for (int i = 3; i < n + 1; ++i) {
            dp[i] = std::max(nums[i - 1] + dp[i - 2], dp[i - 1]);
        }

        return dp[n];
        */
        
        int n = nums.size();
        if (n == 1) {
            return nums[0];
        }

        std::vector<int> dp(n + 1);
        dp[1] = nums[0];
        dp[2] = std::max(nums[0], nums[1]);
        for (int h = 2; h <= n; ++h) {
            dp[h] = std::max(dp[h - 1], dp[h - 2] + nums[h - 1]);
        }

        return dp[n];
    }

    int recursive2(std::vector<int>& nums, int now, std::vector<int>& mem) {
        if (now >= nums.size()) {
            return 0;
        }

        if (mem[now] != -1) {
            return mem[now];
        }
        int max = -1;

        max = std::max(recursive2(nums, now + 1, mem), recursive2(nums, now + 2, mem) + nums[now]);

        mem[now] = max;
        return max;
    }

    int iterative(std::vector<int>& nums) {
        int max = -1;
        std::vector<int> mem(nums.size(), -1);
        mem[nums.size() - 1] = nums[nums.size() - 1];
        mem[nums.size() - 2] = nums[nums.size() - 2];
        
        for (int i = nums.size() - 3; i > -1; --i) {
            int inner_max = mem[i];

            for (int now = i + 2; now < nums.size(); ++now) {
                if (mem[now] != -1) {
                    inner_max = std::max(inner_max, mem[now]);
                    continue;
                }

                inner_max = std::max(inner_max, mem[now]);
                mem[now] = inner_max;
            }

            max = std::max(max, nums[i] + inner_max);
            mem[i] = max;
        }

        return max;
    }

    int recursive(std::vector<int>& nums, int now, std::vector<int>& mem) {
        if (now >= nums.size()) {
            return 0;
        }

        if (mem[now] != -1) {
            return mem[now];
        }
        int max = -1;

        for (int i = 2; i < nums.size(); ++i) {
            max = std::max(max, nums[now] + recursive(nums, now + i, mem));
        }

        mem[now] = max;

        return max;
    }

public:
    int rob(vector<int>& nums) {
        //edge cases
        if (nums.size() == 1) {
            return nums[0];
        }

        if (nums.size() == 2) {
            return std::max(nums[0], nums[1]);
        }

        if (nums.size() == 3) {
            return std::max(nums[0] + nums[2], nums[1]);
        }

        //recursive way
        /*
        int max = -1;
        std::vector<int> mem(nums.size(), -1);

        for (int i = 0; i < nums.size(); ++i) {
            max = std::max(max, recursive(nums, i, mem));
        }

        return max;
        */

        //iterative way
        //return iterative(nums);

        //better recursive
        /*
        std::vector<int> mem(nums.size(), -1);
        return recursive2(nums, 0, mem);
        */

        //better iterative
        return iterative2(nums);
    }
};