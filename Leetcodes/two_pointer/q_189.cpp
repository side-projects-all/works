/*
Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.

 

Example 1:

Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]

Example 2:

Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]

 

Constraints:

    1 <= nums.length <= 10^5
    -2^31 <= nums[i] <= 2^31 - 1
    0 <= k <= 10^5


*/

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        //by copy
        /*
        std::vector<int> copy(nums.size(), 0);

        for (int i = 0; i < copy.size(); ++i) {
            int pos = (i + k) % copy.size();
            copy[pos] = nums[i];
        }

        for (int i = 0; i < nums.size(); ++i) {
            nums[i] = copy[i];
        }
        */

        //by cycle
        /*
        k = k % nums.size();

        if (k == 0) {
            return;
        }

        int count = 0;

        for (int i = 0; count < nums.size(); ++i) {
            int curr = i;
            int prev_val = nums[curr];

            do {
                int next = (curr + k) % nums.size();
                int tmp = nums[next];

                nums[next] = prev_val;
                prev_val = tmp;
                curr = next;

                count += 1;
            } while (curr != i);
        }
        */

        //by reverse
        k %= nums.size();
        std::reverse(nums.begin(), nums.end());
        std::reverse(nums.begin(), nums.begin() + k);
        std::reverse(nums.begin() + k, nums.end());
    }
};