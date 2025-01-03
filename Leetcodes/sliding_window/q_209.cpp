/*
Given an array of positive integers nums and a positive integer target, return the minimal length of a
subarray
whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.

 

Example 1:

Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.

Example 2:

Input: target = 4, nums = [1,4,4]
Output: 1

Example 3:

Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0

 

Constraints:

    1 <= target <= 10^9
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^4

*/

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {

        //using two pointer
        
        int sum = 0;
        int total = nums.size() + 1;    //using total size + 1 as upper bound
        int left = 0;

        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];

            while (sum >= target) {
                //compare with total used before to get minimum value
                total = std::min(total, i + 1 - left);

                //left is a pointer we set from the beginning
                sum -= nums[left];
                left += 1;
            }
        }
        
        return (total != nums.size() + 1) ? total : 0;
        

        //using binary search
        /*
        int len = nums.size();
        if (len == 0) {
            return 0;
        }

        int upper_bound = nums.size() + 1;
        int min = nums.size() + 1;
        std::vector<int> sums(len + 1, 0);  //sum that acclumulates before every element

        for (int i = 1; i <= len; ++i) {
            sums[i] = sums[i - 1] + nums[i - 1];
        }

        for (int i = 1; i <= len; ++i) {
            int to_find = target + sums[i - 1];
            auto bound = lower_bound(sums.begin(), sums.end(), to_find);

            if (bound != sums.end()) {
                min = std::min(min, static_cast<int>(bound - (sums.begin() + i - 1)));
            }
        }

        return (min != upper_bound) ? min : 0;
        */
    }
};