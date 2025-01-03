/*
Given an integer array nums, reorder it such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

You may assume the input array always has a valid answer.

 

Example 1:

Input: nums = [3,5,2,1,6,4]
Output: [3,5,1,6,2,4]
Explanation: [1,6,2,5,3,4] is also accepted.

Example 2:

Input: nums = [6,6,5,6,3,8]
Output: [6,6,5,6,3,8]

 

Constraints:

    1 <= nums.length <= 5 * 10^4
    0 <= nums[i] <= 10^4
    It is guaranteed that there will be an answer for the given input nums.

 

Follow up: Could you solve the problem in O(n) time complexity?

*/

class Solution {
    void byGreedy(std::vector<int>& nums) {
        for (int i = 1; i < nums.size(); ++i) {

            if (((i % 2 == 0) && nums[i] > nums[i - 1]) || ((i % 2 == 1) && nums[i] < nums[i - 1])) {
                std::swap(nums[i], nums[i - 1]);
            }
        }
    }

    void bySort(std::vector<int>& nums) {
        
        std::sort(nums.begin(), nums.end());

        for (int i = 1; i < nums.size() - 1; i += 2) {
            std::swap(nums[i], nums[i + 1]);
        }

        //bool larger = true;
        /*
        for (int i = 1; i < nums.size(); ++i) {
            
            if (larger) {

                //switch if it was smaller than prev
                if (nums[i] < nums[i - 1]) {
                    std::swap(nums[i], nums[i - 1]);

                }
            } else {
                //switch if it was larger than prev
                if (nums[i] > nums[i - 1]) {
                    std::swap(nums[i], nums[i - 1]);
                }
            }

            larger = !larger;
            
        }
        */
    }

public:
    void wiggleSort(vector<int>& nums) {
        //bySort(nums);
        byGreedy(nums);
    }
};