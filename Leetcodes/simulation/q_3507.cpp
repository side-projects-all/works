/*
Given an array nums, you can perform the following operation any number of times:

    Select the adjacent pair with the minimum sum in nums. If multiple such pairs exist, choose the leftmost one.
    Replace the pair with their sum.

Return the minimum number of operations needed to make the array non-decreasing.

An array is said to be non-decreasing if each element is greater than or equal to its previous element (if it exists).

 

Example 1:

Input: nums = [5,2,3,1]

Output: 2

Explanation:

    The pair (3,1) has the minimum sum of 4. After replacement, nums = [5,2,4].
    The pair (2,4) has the minimum sum of 6. After replacement, nums = [5,6].

The array nums became non-decreasing in two operations.

Example 2:

Input: nums = [1,2,2]

Output: 0

Explanation:

The array nums is already sorted.

 

Constraints:

    1 <= nums.length <= 50
    -1000 <= nums[i] <= 1000


*/

class Solution {
private:
    bool is_non_decreasing(vector<int>& nums) {
        int n = nums.size();
        for (int i = 1; i < n; ++i) {
            if (nums[i] < nums[i - 1]) {
                return false;
            }
        }
        
        return true;
    }
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return 0;
        }
        
        if (n == 2) {
            return nums[1] < nums[0];
        }
        
        int move = 0;
        
        while (!is_non_decreasing(nums)) {
            int min_pos = 0;
            int min_sum = INT_MAX;

            for (int i = 1; i < nums.size(); ++i) {

                if (nums[i - 1] + nums[i] < min_sum) {
                    min_pos = i;
                    min_sum = nums[i - 1] + nums[i];
                }
            }
            
            nums[min_pos - 1] += nums[min_pos];
            nums.erase(nums.begin() + min_pos);
            ++move;
        }
        
        
        
        return move;
    }
};