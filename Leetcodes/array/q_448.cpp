/*
Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.

 
Example 1:

Input: nums = [4,3,2,7,8,2,3,1]
Output: [5,6]

Example 2:

Input: nums = [1,1]
Output: [2]

 

Constraints:

    n == nums.length
    1 <= n <= 10^5
    1 <= nums[i] <= n

*/

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        std::vector<int> result;
        std::vector<int> visited(nums.size(), 0);

        for (int i = 0; i < nums.size(); ++i) {
            if (visited[nums[i] - 1] == 0) {
                visited[nums[i] - 1] = -1;
            }
        }

        for (int i = 0; i < visited.size(); ++i) {
            if (visited[i] == 0) {
                result.push_back(i + 1);
            }
        }
        
        return result;
    }
};