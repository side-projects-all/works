/*
Given an integer array nums of length n and an integer target, find three integers in nums such that the sum is closest to target.

Return the sum of the three integers.

You may assume that each input would have exactly one solution.

 

Example 1:

Input: nums = [-1,2,1,-4], target = 1
Output: 2
Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

Example 2:

Input: nums = [0,0,0], target = 1
Output: 0
Explanation: The sum that is closest to the target is 0. (0 + 0 + 0 = 0).

 

Constraints:

    3 <= nums.length <= 500
    -1000 <= nums[i] <= 1000
    -10^4 <= target <= 10^4


*/

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int diff = INT_MAX;
        std::sort(nums.begin(), nums.end());
        int N = nums.size();
        
        //two pointer
        for (int i = 0; i < N && diff != 0; ++i) {
            int left = i + 1;
            int right = N - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (std::abs(target - sum) < std::abs(diff)) {
                    diff = target - sum;
                }

                if (sum < target) {
                    ++left;
                } else {
                    --right;
                }
            }
        }

        //binary search
        /*
        for (int i = 0; i < N && diff != 0; ++i) {
            for (int j = i + 1; j < N - 1; ++j) {
                int rest = target - nums[i] - nums[j];
                int left = j + 1;
                int right = N - 1;
                while (left < right) {
                    int mid = left + (right - left) / 2;

                    if (nums[mid] < rest) {
                        left = mid + 1;
                    } else {
                        right = mid;
                    }
                }

                int hi = left;
                int lo = left - 1;
                if (hi < N && std::abs(rest - nums[hi]) < std::abs(diff)) {
                    diff = rest - nums[hi];
                }

                if (lo > j && std::abs(rest - nums[lo]) < std::abs(diff)) {
                    diff = rest - nums[lo];
                }
            }
        }
        */
        
        return target - diff;
    }
};