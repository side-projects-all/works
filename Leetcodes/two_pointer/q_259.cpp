/*
Given an array of n integers nums and an integer target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.

 

Example 1:

Input: nums = [-2,0,1,3], target = 2
Output: 2
Explanation: Because there are two triplets which sums are less than 2:
[-2,0,1]
[-2,0,3]

Example 2:

Input: nums = [], target = 0
Output: 0

Example 3:

Input: nums = [0], target = 0
Output: 0

 

Constraints:

    n == nums.length
    0 <= n <= 3500
    -100 <= nums[i] <= 100
    -100 <= target <= 100


*/

class Solution {
private:
    int by_binary_search(vector<int>& nums, int& target, int& n) {
        int cnt = 0;
        for (int i = 0; i < n - 2; ++i) {

            int sum = 0;
            for (int j = i + 1; j < n - 1; ++j) {
                /*
                int k = std::lower_bound(nums.begin() + j, nums.end(), target - nums[i] - nums[j]) - nums.begin() - 1;

                if (k >= j) {
                    sum += k - j;
                }
                */

                int b = j;
                int e = n - 1;
                while (b < e) {
                    int mid = (b + e + 1) / 2;
                    if (nums[mid] < target - nums[i] - nums[j]) {
                        b = mid;
                    } else {
                        e = mid - 1;
                    }
                }
                
                sum += b - j;
            }

            cnt += sum;
        }

        return cnt;
    }
    int by_two_ptr(vector<int>& nums, int& target, int& n) {
        

        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            int j = i + 1;
            int k = n - 1;

            while (j < k) {
                if (nums[i] + nums[j] + nums[k] < target) {
                    cnt += k - j;
                    ++j;

                } else {
                    --k;
                }
            }
        }

        return cnt;
    }
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int n = nums.size();
        if (n < 3) {
            return 0;
        }

        if (n == 3) {
            return nums[0] + nums[1] + nums[2] < target;
        }

        std::sort(nums.begin(), nums.end());

        return by_binary_search(nums, target, n);
        //return by_two_ptr(nums, target, n);
    }
};