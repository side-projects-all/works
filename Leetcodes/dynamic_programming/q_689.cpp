/*
Given an integer array nums and an integer k, find three non-overlapping subarrays of length k with maximum sum and return them.

Return the result as a list of indices representing the starting position of each interval (0-indexed). If there are multiple answers, return the lexicographically smallest one.

 

Example 1:

Input: nums = [1,2,1,2,6,7,5,1], k = 2
Output: [0,3,5]
Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.

Example 2:

Input: nums = [1,2,1,2,1,2,1,2,1], k = 2
Output: [0,2,4]

 

Constraints:

    1 <= nums.length <= 2 * 10^4
    1 <= nums[i] < 2^16
    1 <= k <= floor(nums.length / 3)


*/

class Solution {
private:
    vector<int> by_iterative_dp(vector<int>& nums, int& k) {
        int n = nums.size();
        std::vector<int> prefix_sum(n + 1);
        for (int i = 1; i <= n; ++i) {
            prefix_sum[i] = prefix_sum[i - 1] + nums[i - 1];
        }

        std::vector<std::vector<int>> best_sum(4, std::vector<int>(n + 1));
        std::vector<std::vector<int>> best_i(4, std::vector<int>(n + 1));

        for (int subarr_cnt = 1; subarr_cnt <= 3; ++subarr_cnt) {
            for (int end = k * subarr_cnt; end <= n; ++end) {
                int curr_sum = prefix_sum[end] - prefix_sum[end - k] + best_sum[subarr_cnt - 1][end - k];

                if (curr_sum > best_sum[subarr_cnt][end - 1]) {
                    best_sum[subarr_cnt][end] = curr_sum;
                    best_i[subarr_cnt][end] = end - k;

                } else {
                     best_sum[subarr_cnt][end] = best_sum[subarr_cnt][end - 1];
                     best_i[subarr_cnt][end] = best_i[subarr_cnt][end - 1];
                }
            }
        }

        std::vector<int> ans(3);
        int curr_end = n;
        for (int subarr_i = 3; subarr_i >= 1; --subarr_i) {
            ans[subarr_i - 1] = best_i[subarr_i][curr_end];
            curr_end = ans[subarr_i - 1];
        }

        return ans;
    }
    int recursive(std::vector<int>& sums, int& k, int i, int rest, std::vector<std::vector<int>>& mem) {
        if (rest == 0) {
            return 0;
        }

        if (i >= sums.size()) {
            return rest > 0 ? INT_MIN : 0;
        }

        if (mem[i][rest] != -1) {
            return mem[i][rest];
        }

        int use_curr = sums[i] + recursive(sums, k, i + k, rest - 1, mem);
        int not_use = recursive(sums, k, i + 1, rest, mem);

        mem[i][rest] = std::max(use_curr, not_use);

        return mem[i][rest];
    }

    void dfs(std::vector<int>& sums, int& k, int i, int rest, std::vector<std::vector<int>>& mem, std::vector<int>& indices) {

        if (rest == 0) {
            return;
        }

        if (i >= sums.size()) {
            return;
        }

        int use_curr = sums[i] + recursive(sums, k, i + k, rest - 1, mem);
        int not_use = recursive(sums, k, i + 1, rest, mem);

        if (use_curr >= not_use) {
            indices.push_back(i);
            dfs(sums, k, i + k, rest - 1, mem, indices);
        } else {
            dfs(sums, k, i + 1, rest, mem, indices);
        }   
    }

    vector<int> by_recursive_dp_dfs(vector<int>& nums, int& k) {

        //n represents how many windows
        int n = nums.size() - k + 1;

        std::vector<int> sums(n);
        int window_sum = 0;
        //first window
        for (int i = 0; i < k; ++i) {
            window_sum += nums[i];
        }
        sums[0] = window_sum;   //this is first window sum

        //handle rest window sums
        for (int i = k; i < nums.size(); ++i) {
            window_sum = window_sum - nums[i - k] + nums[i];
            sums[i - k + 1] = window_sum;
        }

        std::vector<std::vector<int>> mem(n, std::vector<int>(4, -1));
        std::vector<int> indices;

        recursive(sums, k, 0, 3, mem);
        dfs(sums, k, 0, 3, mem, indices);

        return indices;
    }
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        //return by_recursive_dp_dfs(nums, k);
        return by_iterative_dp(nums, k);
    }
};