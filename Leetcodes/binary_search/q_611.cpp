/*
Given an integer array nums, return the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle.

 

Example 1:

Input: nums = [2,2,3,4]
Output: 3
Explanation: Valid combinations are: 
2,3,4 (using the first 2)
2,3,4 (using the second 2)
2,2,3

Example 2:

Input: nums = [4,2,3,4]
Output: 4

 

Constraints:

    1 <= nums.length <= 1000
    0 <= nums[i] <= 1000


*/

class Solution {
private:
    int byLinear(vector<int>& nums) {
        int cnt = 0;
        int N = nums.size();

        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < N - 2; ++i) {
            int t = i + 2;

            for (int s = i + 1; s < N - 1 && nums[i] != 0; ++s) {
                while (t < N && nums[i] + nums[s] > nums[t]) {
                    ++t;
                }

                cnt += t - s - 1;
            }
        }

        return cnt;
    }

    int binarySearch(vector<int>& nums, int left, int right, int sum) {
        
        int N = nums.size();

        while (left <= right && right < N) {
            int mid = left + (right - left) / 2;

            if (nums[mid] >= sum) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return left;
    }

    int byBS(vector<int>& nums) {
        int N = nums.size();
        int cnt = 0;

        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < N; ++i) {
            //third side
            int t = i + 2;

            //s is second side
            for (int s = i + 1; s < N - 1 && nums[i] != 0; ++s) {
                t = binarySearch(nums, t, N - 1, nums[i] + nums[s]);
                cnt += t - s - 1;
            }
        }

        return cnt;
    }
public:
    int triangleNumber(vector<int>& nums) {
        //return byBS(nums);
        return byLinear(nums);
    }
};