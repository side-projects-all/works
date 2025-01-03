/*
Given an integer array nums, return the value of the bitwise OR of the sum of all possible subsequences in the array.

A subsequence is a sequence that can be derived from another sequence by removing zero or more elements without changing the order of the remaining elements.

 

Example 1:

Input: nums = [2,1,0,3]
Output: 7
Explanation: All possible subsequence sums that we can have are: 0, 1, 2, 3, 4, 5, 6.
And we have 0 OR 1 OR 2 OR 3 OR 4 OR 5 OR 6 = 7, so we return 7.

Example 2:

Input: nums = [0,0,0]
Output: 0
Explanation: 0 is the only possible subsequence sum we can have, so we return 0.

 

Constraints:

    1 <= nums.length <= 10^5
    0 <= nums[i] <= 10^9


*/

class Solution {
private:
    long long prefixSum(vector<int>& nums) {
        long long ans = 0;
        long long prefixSum = 0;

        for (const int n : nums) {
            prefixSum += n;

            ans |= (n | prefixSum);
        }

        return ans;
    }
    long long byBitsOperation(vector<int>& nums) {
        std::vector<long long> bitSetCnts(64);
        long long ans = 0;

        for (int n : nums) {


            for (int i = 0; i < 31; ++i) {
                if (n & (1 << i)) {
                    ++bitSetCnts[i];
                }
            }
        }

        for (int i = 0; i < 63; ++i) {
            if (bitSetCnts[i]) {
                ans |= (1LL << i);
            }

            bitSetCnts[i + 1] += bitSetCnts[i] / 2;
        }

        return ans;
    }
public:
    long long subsequenceSumOr(vector<int>& nums) {
        //return byBitsOperation(nums);
        return prefixSum(nums);
    }
};
