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
    void onePass(vector<int>& nums) {
        int p0 = 0;
        int curr = 0;
        int p2 = nums.size() - 1;

        while (curr <= p2) {
            if (nums[curr] == 0) {
                std::swap(nums[curr], nums[p0]);
                ++curr;
                ++p0;

            } else if (nums[curr] == 2) {
                std::swap(nums[curr], nums[p2]);
                --p2;
            } else {
                ++curr;
            }
        }

    }
    void byCounting(vector<int>& nums) {
        int arr[3]{ 0, 0, 0 };
        for (int n : nums) {
            ++arr[n];
        }

        int index = 0;
        for (int i = 0; i < nums.size();) {

            if (arr[index] == 0) {
                ++index;
                continue;
            } else {
                --arr[index];
                nums[i] = index;
                ++i;
            }
        }
    }
public:
    void sortColors(vector<int>& nums) {

        //byCounting(nums);
        onePass(nums);
    }
};