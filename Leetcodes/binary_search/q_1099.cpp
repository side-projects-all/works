/*
Given an array nums of integers and integer k, return the maximum sum such that there exists i < j with nums[i] + nums[j] = sum and sum < k. If no i, j exist satisfying this equation, return -1.

 

Example 1:

Input: nums = [34,23,1,24,75,33,54,8], k = 60
Output: 58
Explanation: We can use 34 and 24 to sum 58 which is less than 60.

Example 2:

Input: nums = [10,20,30], k = 15
Output: -1
Explanation: In this case it is not possible to get a pair sum less that 15.

 

Constraints:

    1 <= nums.length <= 100
    1 <= nums[i] <= 1000
    1 <= k <= 2000


*/

class Solution {
public:
    int twoSumLessThanK(vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end());

        int N = nums.size();
        int left = 0;
        int right = N - 1;
        int answer = -1;

        //using tow pointer perform better!!
        /*
        
        while (left < right) {
            int sum = nums[left] + nums[right];

            if (sum < k) {
                answer = std::max(answer, sum);
                ++left;
            } else {
                --right;
            }
        }

        
        */

        //using binary search
        if (nums.size() <= 1) {
            return -1;
        }

        for (int i = 0; i < nums.size() && nums[i] < k; ++i) {
            int rest_val = k - nums[i];
            left = i;
            right = N - 1;

            while (left <= right) {
                int mid = left + (right - left) / 2;

                if (nums[mid] < rest_val) {
                    left = mid + 1;
                    
                } else {
                    right = mid - 1; 
                } 
            }
            
            if (left - 1 > i) {
                answer = std::max(answer, nums[left - 1] + nums[i]);
            }
            
        }
        
        return answer;
    }
};