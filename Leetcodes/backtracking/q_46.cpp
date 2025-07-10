/*
Given an array nums of distinct integers, return all the possible
permutations
. You can return the answer in any order.

 

Example 1:

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

Example 2:

Input: nums = [0,1]
Output: [[0,1],[1,0]]

Example 3:

Input: nums = [1]
Output: [[1]]

 

Constraints:

    1 <= nums.length <= 6
    -10 <= nums[i] <= 10
    All the integers of nums are unique.


*/

class Solution {
private:
    void back_tracking(vector<int>& nums, std::vector<std::vector<int>>& ans, int i) {
        if (i == nums.size()) {
            ans.push_back(nums);
            return;
        }

        for (int j = i; j < nums.size(); ++j) {
            std::swap(nums[i], nums[j]);
            back_tracking(nums, ans, i + 1);
            std::swap(nums[i], nums[j]);
        }
    }
    vector<vector<int>> by_back_tracking(vector<int>& nums) {
        std::vector<std::vector<int>> ans;
        std::vector<int> curr;
        back_tracking(nums, ans, 0);      
        
        return ans;
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        return by_back_tracking(nums);
    }
};