/*
You are given a 0-indexed integer array nums and an integer p. Find p pairs of indices of nums such that the maximum difference amongst all the pairs is minimized. Also, ensure no index appears more than once amongst the p pairs.

Note that for a pair of elements at the index i and j, the difference of this pair is |nums[i] - nums[j]|, where |x| represents the absolute value of x.

Return the minimum maximum difference among all p pairs. We define the maximum of an empty set to be zero.

 

Example 1:

Input: nums = [10,1,2,7,1,3], p = 2
Output: 1
Explanation: The first pair is formed from the indices 1 and 4, and the second pair is formed from the indices 2 and 5. 
The maximum difference is max(|nums[1] - nums[4]|, |nums[2] - nums[5]|) = max(0, 1) = 1. Therefore, we return 1.

Example 2:

Input: nums = [4,2,1,2], p = 1
Output: 0
Explanation: Let the indices 1 and 3 form a pair. The difference of that pair is |2 - 2| = 0, which is the minimum we can attain.

 

Constraints:

    1 <= nums.length <= 10^5
    0 <= nums[i] <= 10^9
    0 <= p <= (nums.length)/2


*/

class Solution {
private:
    bool has_valid_pairs(vector<int>& nums, int& threshold, int& p) {
        
        int n = nums.size();
        int cnt = 0;

        for (int i = 0; i < n - 1; ++i) {
            if (nums[i + 1] - nums[i] <= threshold) {
                ++cnt;
                ++i;
            }

            if (cnt >= p) {
                return true;
            }
        }

        return false;
    }

    int by_bs_greedy(vector<int>& nums, int p) {
        if (p == 0) {
            return 0;
        }

        int n = nums.size();
        std::sort(nums.begin(), nums.end());
        int left = 0;
        int right = nums[n - 1] - nums[0];

        int ans = 0;
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (has_valid_pairs(nums, mid, p)) {
                ans = mid;
                right = mid - 1;

            } else {
                left = mid + 1;
            }
        }

        return ans;
    }
public:
    int minimizeMax(vector<int>& nums, int p) {
        return by_bs_greedy(nums, p);
    }
};