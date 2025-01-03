/*
You are given an inclusive range [lower, upper] and a sorted unique integer array nums, where all elements are within the inclusive range.

A number x is considered missing if x is in the range [lower, upper] and x is not in nums.

Return the shortest sorted list of ranges that exactly covers all the missing numbers. That is, no element of nums is included in any of the ranges, and each missing number is covered by one of the ranges.

 

 

Example 1:

Input: nums = [0,1,3,50,75], lower = 0, upper = 99
Output: [[2,2],[4,49],[51,74],[76,99]]
Explanation: The ranges are:
[2,2]
[4,49]
[51,74]
[76,99]

Example 2:

Input: nums = [-1], lower = -1, upper = -1
Output: []
Explanation: There are no missing ranges since there are no missing numbers.

 

Constraints:

    -10^9 <= lower <= upper <= 10^9
    0 <= nums.length <= 100
    lower <= nums[i] <= upper
    All the values of nums are unique.


*/

class Solution {
private:
    vector<vector<int>> naive(vector<int>& nums, int lower, int upper) {

        int left = lower;
        int i = 0;
        vector<vector<int>> result;
        while (left <= upper) {
            if (i == nums.size()) {
                result.push_back({left, upper});
                return result;

            } else {
                if (nums[i] != left) {
                    result.push_back({left, nums[i] - 1});
                }

                left = nums[i] + 1;
                ++i;
            }
            
        }
        return result;
        /*
        std::vector<std::vector<int>> result;

        if (nums.size() == 0) {
            result.push_back({ lower, upper });
            return result;
        }

        if (lower + 1 < nums[0]) {
            result.push_back({ lower, nums[0] - 1 });
        } else if (lower + 1 == nums[0]) {
            result.push_back({ lower, lower });
        }

        for (int i = 0; i < nums.size() - 1; ++i) {
            if (nums[i] + 1 < nums[i + 1]) {
                result.push_back({ nums[i] + 1, nums[i + 1] - 1 });
            }
        }

        if (nums[nums.size() - 1] + 1 < upper) {
            result.push_back({ nums[nums.size() - 1] + 1, upper });
        } else if (nums[nums.size() - 1] + 1 == upper) {
            result.push_back({ upper, upper });
        }

        return result;
        */
    }

public:
    vector<vector<int>> findMissingRanges(vector<int>& nums, int lower, int upper) {
        return naive(nums, lower, upper);
    }
};