/*
Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:

    0 <= a, b, c, d < n
    a, b, c, and d are distinct.
    nums[a] + nums[b] + nums[c] + nums[d] == target

You may return the answer in any order.

 

Example 1:

Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

Example 2:

Input: nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]

 

Constraints:

    1 <= nums.length <= 200
    -10^9 <= nums[i] <= 10^9
    -10^9 <= target <= 10^9


*/

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());

        return k_sum(nums, target, 0, 4);
    }

private:
    std::vector<std::vector<int>> k_sum(std::vector<int>& nums, long target, int s, int k) {
        std::vector<std::vector<int>> ans;

        if (s == nums.size()) {
            return ans;
        }

        int avg = target / k;
        if (nums[s] > avg || avg > nums.back()) {
            return ans;
        }

        if (k == 2) {
            return two_sum(nums, target, s);
        }

        for (int i = s; i < nums.size(); ++i) {

            if (i == s || nums[i] != nums[i - 1]) {
                for (std::vector<int>& sub : k_sum(nums, target - nums[i], i + 1, k - 1)) {
                    ans.push_back({nums[i]});
                    ans.back().insert(std::end(ans.back()), sub.begin(), sub.end());
                }
            }
        }
        return ans;
    }

    std::vector<std::vector<int>> two_sum(std::vector<int>& nums, long target, int s) {
        std::vector<std::vector<int>> ans;
        int left = s;
        int right = nums.size() - 1;

        while (left < right) {
            int sum = nums[left] + nums[right];

            if (sum < target || (left > s && nums[left] == nums[left - 1])) {
                ++left;

            } else if (sum > target || (right < nums.size() - 1 && nums[right] == nums[right + 1])) {
                --right;

            } else {
                ans.push_back({nums[left], nums[right]});
                ++left;
                --right;
            }
        }

        return ans;
    }
};