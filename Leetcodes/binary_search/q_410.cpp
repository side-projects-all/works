/*
Given an integer array nums and an integer k, split nums into k non-empty subarrays such that the largest sum of any subarray is minimized.

Return the minimized largest sum of the split.

A subarray is a contiguous part of the array.

 

Example 1:

Input: nums = [7,2,5,10,8], k = 2
Output: 18
Explanation: There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8], where the largest sum among the two subarrays is only 18.

Example 2:

Input: nums = [1,2,3,4,5], k = 2
Output: 9
Explanation: There are four ways to split nums into two subarrays.
The best way is to split it into [1,2,3] and [4,5], where the largest sum among the two subarrays is only 9.

 

Constraints:

    1 <= nums.length <= 1000
    0 <= nums[i] <= 10^6
    1 <= k <= min(50, nums.length)


*/

class Solution {
private:
    int by_iterative_dp(vector<int>& nums, int k) {
        int n = nums.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1));

        std::vector<int> prefix_sum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix_sum[i + 1] = prefix_sum[i] + nums[i];
        }

        for (int sub_arr_cnt = 1; sub_arr_cnt <= k; ++sub_arr_cnt) {
            for (int curr = 0; curr < n; ++curr) {
                if (sub_arr_cnt == 1) {
                    dp[curr][sub_arr_cnt] = prefix_sum[n] - prefix_sum[curr];
                    continue;
                }

                int min_max_sum = INT_MAX;
                for (int i = curr; i <= n - sub_arr_cnt; ++i) {

                    int first_split_sum = prefix_sum[i + 1] - prefix_sum[curr];
                    int max_split_sum = std::max(first_split_sum, dp[i + 1][sub_arr_cnt - 1]);

                    min_max_sum = std::min(min_max_sum, max_split_sum);

                    if (first_split_sum >= min_max_sum) {
                        break;
                    }
                }

                dp[curr][sub_arr_cnt] = min_max_sum;
            }
        }

        return dp[0][k];
    }

    int recursive(std::vector<int>& prefix_sum, std::vector<std::vector<int>>& mem, int curr, int sub_arr_cnt) {
        int n = prefix_sum.size() - 1;

        if (mem[curr][sub_arr_cnt] != -1) {
            return mem[curr][sub_arr_cnt];
        }

        if (sub_arr_cnt == 1) {
            return mem[curr][sub_arr_cnt] = prefix_sum[n] - prefix_sum[curr];
        }

        int min_max_sum = INT_MAX;
        for (int i = curr; i <= n - sub_arr_cnt; ++i) {

            int first_split_sum = prefix_sum[i + 1] - prefix_sum[curr];
            int max_split_sum = std::max(first_split_sum, recursive(prefix_sum, mem, i + 1, sub_arr_cnt - 1));

            min_max_sum = std::min(min_max_sum, max_split_sum);

            if (first_split_sum >= min_max_sum) {
                break;
            }
        }

        return mem[curr][sub_arr_cnt] = min_max_sum;
    }

    int by_recursive_dp(vector<int>& nums, int& k) {
        int n = nums.size();
        std::vector<std::vector<int>> mem(n + 1, std::vector<int>(k + 1, -1));

        std::vector<int> prefix_sum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix_sum[i + 1] = prefix_sum[i] + nums[i];
        }

        return recursive(prefix_sum, mem, 0, k);
    }

    int minSubarraysRequired(std::vector<int>& nums, int maxSumAllowed) {
        int currentSum = 0;
        int splitsRequired = 0;

        for (int element : nums) {
            if (currentSum + element <= maxSumAllowed) {
                currentSum += element;
            } else {
                currentSum = element;
                ++splitsRequired;
            }
        }

        return splitsRequired + 1;
    }

    int by_binary_search(vector<int>& nums, int& k) {
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        int maxElement = *std::max_element(nums.begin(), nums.end());

        int left = maxElement;
        int right = sum;
        int minLargestSplitSum = 0;

        while (left <= right) {
            int maxSumAllowed = left + (right - left) / 2;

            if (minSubarraysRequired(nums, maxSumAllowed) <= k) {
                right = maxSumAllowed - 1;
                minLargestSplitSum = maxSumAllowed;
            } else {
                left = maxSumAllowed + 1;
            }
        }

        return minLargestSplitSum;
    }
public:
    int splitArray(vector<int>& nums, int k) {
        //return by_binary_search(nums, k);
        //return by_recursive_dp(nums, k);
        return by_iterative_dp(nums, k);
    }
};