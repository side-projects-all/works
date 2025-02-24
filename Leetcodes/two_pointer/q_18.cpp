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
private:
    std::vector<std::vector<int>> two_sum(vector<int>& nums, long target, int b) {
        std::vector<std::vector<int>> ans;
        int e = nums.size() - 1;

        while (b < e) {

            if (nums[b] + nums[e] == target) {
                ans.push_back({nums[b], nums[e]});
                ++b;
                --e;

                while (b < e && nums[b] == nums[b - 1]) {
                    ++b;
                }
            } else if (nums[b] + nums[e] > target) {
                --e;

            } else {
                ++b;
            }
        }

        return ans;
    }

    std::vector<std::vector<int>> k_sum(vector<int>& nums, int& n, long target, int b, int k) {
        std::vector<std::vector<int>> ans;
        
        int avg = target / k;
        if (nums[0] > avg || nums[n - 1] < avg) {
            return ans;
        }

        if (k == 2) {
            return two_sum(nums, target, b);
        }

        for (int i = b; i < n; ++i) {
            if (i == b || nums[i] != nums[i - 1]) {
                
                for (std::vector<int>& v : k_sum(nums, n, target - nums[i], i + 1, k - 1)) {
                    ans.push_back({nums[i]});
                    ans.back().insert(ans.back().end(), v.begin(), v.end());
                }
            }
        }

        return ans;
    }
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        if (n < 4) {
            return {};
        }

        return k_sum(nums, n, target, 0, 4);
    }
};