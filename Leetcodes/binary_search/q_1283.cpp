/*
Given an array of integers nums and an integer threshold, we will choose a positive integer divisor, divide all the array by it, and sum the division's result. Find the smallest divisor such that the result mentioned above is less than or equal to threshold.

Each result of the division is rounded to the nearest integer greater than or equal to that element. (For example: 7/3 = 3 and 10/2 = 5).

The test cases are generated so that there will be an answer.

 

Example 1:

Input: nums = [1,2,5,9], threshold = 6
Output: 5
Explanation: We can get a sum to 17 (1+2+5+9) if the divisor is 1. 
If the divisor is 4 we can get a sum of 7 (1+1+2+3) and if the divisor is 5 the sum will be 5 (1+1+1+2). 

Example 2:

Input: nums = [44,22,33,11,1], threshold = 5
Output: 44

 

Constraints:

    1 <= nums.length <= 5 * 10^4
    1 <= nums[i] <= 10^6
    nums.length <= threshold <= 10^6


*/

class Solution {
private:
    int by_binary_search(vector<int>& nums, int& threshold) {
        int n = nums.size();
        if (n == 1) {
            return nums[0] % threshold == 0 ? nums[0] / threshold : nums[0] / threshold + 1;
        }

        int b = 1;
        int e = nums[0];
        for (int i = 1; i < n; ++i) {
            e = std::max(e, nums[i]);
        }

        while (b < e) {
            int mid = b + (e - b) / 2;
            int sum = 0;
            for (int i = 0; i < n; ++i) {

                if (nums[i] % mid != 0) {
                    sum += nums[i] / mid + 1;

                } else {
                    sum += nums[i] / mid;
                }
            }

            if (sum > threshold) {
                b = mid + 1;

            } else {
                e = mid;
            }
        }

        return b;
    }
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        return by_binary_search(nums, threshold);
    }
};