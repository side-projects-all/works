/*
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

 

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]

 

Constraints:

    2 <= nums.length <= 10^4
    -10^9 <= nums[i] <= 10^9
    -10^9 <= target <= 10^9
    Only one valid answer exists.

*/

class Solution {
private:
    vector<int> by_hash_map(vector<int>& nums, int& target) {
        std::unordered_map<int, int> m;

        for (int i = 0; i < nums.size(); ++i) {

            if (m.find(target - nums[i]) != m.end()) {
                return {i, m[target - nums[i]]};
            }

            m[nums[i]] = i;
        }

        return {};
    }
    vector<int> by_binary_search(vector<int>& nums, int& target) {

        
        std::vector<std::pair<int, int>> pair_nums(nums.size());

        for (int i = 0; i < nums.size(); ++i) {
            pair_nums[i] = {nums[i], i};
        }

        std::sort(pair_nums.begin(), pair_nums.end());

        //use the way in leetcode 167
        int left  = 0; 
        int right = nums.size() - 1;
        while (left < right) {
            
            if (pair_nums[left].first + pair_nums[right].first == target) {
                return {pair_nums[left].second, pair_nums[right].second};
            }

            if (pair_nums[left].first + pair_nums[right].first > target) {
                right -= 1;
            } else {
                left += 1;
            }
        }

        return {};

        /*
        for (int i = 0; i < pair_nums.size(); ++i) {

            int j = bs(i + 1, pair_nums.size() - 1, pair_nums, target - pair_nums[i].first);
            if (j != -1) {
                return {pair_nums[i].second, pair_nums[j].second};
            }
        }

        return {};
        */
    }
    /*
    int bs(int left, int right, std::vector<std::pair<int, int>>& pair_nums, int target) {

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (pair_nums[mid].first == target) {
                return mid;
            }

            if (pair_nums[mid].first > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return -1;
    }
    */
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        return by_binary_search(nums, target);
        
        //return by_hash_map(nums, target);
    }
};