/*
Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.

We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.

You must solve this problem without using the library's sort function.

 

Example 1:

Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]

Example 2:

Input: nums = [2,0,1]
Output: [0,1,2]

 

Constraints:

    n == nums.length
    1 <= n <= 300
    nums[i] is either 0, 1, or 2.

*/

class Solution {
private:
    void by_two_ptr(vector<int>& nums) {
        int n = nums.size();
        int red = 0;
        int blue = n - 1;
        int curr = 0;

        while (curr <= blue) {

            if (nums[curr] == 0) {
                std::swap(nums[red], nums[curr]);
                ++red;
                ++curr;

            } else if (nums[curr] == 2) {
                std::swap(nums[blue], nums[curr]);
                --blue;

            } else {
                ++curr;
            }
        }
    }
public:
    void sortColors(vector<int>& nums) {
        by_two_ptr(nums);
    }
};