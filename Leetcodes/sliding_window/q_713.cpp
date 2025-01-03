/*
Given an array of integers nums and an integer k, return the number of contiguous subarrays where the product of all the elements in the subarray is strictly less than k.

 

Example 1:

Input: nums = [10,5,2,6], k = 100
Output: 8
Explanation: The 8 subarrays that have product less than 100 are:
[10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.

Example 2:

Input: nums = [1,2,3], k = 0
Output: 0

 

Constraints:

    1 <= nums.length <= 3 * 10^4
    1 <= nums[i] <= 1000
    0 <= k <= 10^6


*/

class Solution {
private:
    int slidingWindow(vector<int>& nums, int k) {
        if (k <= 1) {
            return 0;
        }
        int N = nums.size();
        int cnt = 0;

        int begin = 0;
        int end = 0;
        int prod = 1;

        //the point is the idea of the range that has product is smaller than k and ends with num[i] 
        while (end < N) {

            prod *= nums[end];

            while (prod >= k) {
                prod /= nums[begin];
                ++begin;                
            }

            cnt += end - begin + 1;
            ++end;
        }

        return cnt;
    }

    //dp 1d array TLE
    int iterative(vector<int>& nums, int k) {
        int N = nums.size();
        int cnt = 0;
        
        //1d array still TLE
        std::vector<int> mem(N, 0);
        for (int i = 0; i < N; ++i) {
            if (nums[i] < k) {
                ++cnt;
            }
            mem[i] = nums[i];
        }

        for (int len = 2; len <= N; ++len) {
            for (int i = 0; i < N; ++i) {

                int end = len + i - 1;
                if (end >= N) {
                    mem[i] = mem[i];

                } else {

                    if (nums[end] * mem[i] < k) {
                        ++cnt;
                        mem[i] = nums[end] * mem[i];

                    } else {
                        mem[i] = k;
                    }
                }
            }
        }

        return cnt;
    }
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        //return iterative(nums, k);
        return slidingWindow(nums, k);
    }
};