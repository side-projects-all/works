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
    void back_tracking(vector<int>& nums, std::vector<std::vector<int>>& ans, int i, std::vector<int>&& curr) {
        if (curr.size() == nums.size()) {
            ans.push_back(curr);
            return;
        }

        for (int j = 0; j < nums.size(); ++j) {

            if (std::find(curr.begin(), curr.end(), nums[j]) == curr.end()) {
                curr.push_back(nums[j]);
                back_tracking(nums, ans, j + 1, std::move(curr));
                curr.pop_back();
            }
        }
    }
    vector<vector<int>> by_back_tracking(vector<int>& nums) {
        std::vector<std::vector<int>> ans;
        back_tracking(nums, ans, 0, std::vector<int>());      
        
        return ans;
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        return by_back_tracking(nums);
    }
};

/*
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        std::vector<std::vector<int>> result;
        std::vector<int> curr;
        backtrack(curr, nums, result);

        return result;
    }

private:

    void backtrack(std::vector<int>& curr, std::vector<int>& nums, std::vector<std::vector<int>>& result) {

        if (curr.size() == nums.size()) {
            result.push_back(curr);
            return;
        }

        for (size_t i = 0; i < nums.size(); ++i) {
            if (std::find(curr.begin(), curr.end(), nums[i]) == curr.end()) {
                curr.push_back(nums[i]);
                backtrack(curr, nums, result);
                curr.pop_back();
            }
        }
    }
};
*/