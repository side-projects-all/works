/*
Given an integer array nums, return the largest integer that only occurs once. If no integer occurs once, return -1.

 

Example 1:

Input: nums = [5,7,3,9,4,9,8,3,1]
Output: 8
Explanation: The maximum integer in the array is 9 but it is repeated. The number 8 occurs only once, so it is the answer.

Example 2:

Input: nums = [9,9,8,8]
Output: -1
Explanation: There is no number that occurs only once.

 

Constraints:

    1 <= nums.length <= 2000
    0 <= nums[i] <= 1000


*/

class Solution {
private:
    int bySort(vector<int>& nums) {
        //corner case
        if (nums.size() == 1) {
            return nums[0];
        }

        std::sort(nums.begin(), nums.end());

        for (int i = nums.size() - 1; i > -1; --i) {
            if (i == 0 || nums[i] != nums[i - 1]) {
                return nums[i];
            }

            while (i > 0 && nums[i] == nums[i - 1]) {
                --i;
            }
        }

        return -1;
    }

    int naiveMap(vector<int>& nums) {
        int max = -1;

        std::unordered_map<int, int> m;

        for (int n : nums) {
            m[n] += 1;
        }

        for (auto& p : m) {
            if (p.second == 1 && p.first > max) {
                max = p.first;
            }
        }

        return max;
    }

public:
    int largestUniqueNumber(vector<int>& nums) {

        //Time complexity of both ways are close!
        //return naiveMap(nums);

        return bySort(nums);
    }
};