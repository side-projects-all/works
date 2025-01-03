/*
Given an integer array nums and an integer k, return true if it is possible to divide this array into k non-empty subsets whose sums are all equal.

 

Example 1:

Input: nums = [4,3,2,3,5,2,1], k = 4
Output: true
Explanation: It is possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.

Example 2:

Input: nums = [1,2,3,4], k = 3
Output: false

 

Constraints:

    1 <= k <= nums.length <= 16
    1 <= nums[i] <= 10^4
    The frequency of each element is in the range [1, 4].


*/

class Solution {
private:

    //this will TLE
    bool naive_Backtracking(vector<int>& nums, int k, int numSum) {
        std::sort(nums.begin(), nums.end(), std::greater<int>());
        
        int N = nums.size();
        int totalSum = 0;
        //std::vector<bool> used(N);
        std::unordered_map<int, bool> mem;
        int perSum = numSum / k;
        int mask = 0;

        std::function<bool(int, int, int)> recurr = [&](int cnt, int currSum, int index) -> bool {
            if (cnt == k - 1) {
                return true;
            }

            if (currSum > perSum) {
                return false;
            }

            if (mem.find(mask) != mem.end()) {
                return mem[mask];
            }

            if (currSum == perSum) {
                return mem[mask] = recurr(cnt + 1, 0, 0);
            }

            for (int i = 0; i < N; ++i) {
                if (((mask >> i) & 1) == 0) {
                    mask = (mask | (1 << i));

                    if (recurr(cnt, currSum + nums[i], i + 1)) {
                        return mem[mask] = true;
                    }
                    
                    mask = (mask ^ (1 << i));
                }
            }

            return mem[mask] = false;
        };

        return recurr(0, 0, 0);
    }
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0) {
            return false;
        }

        return naive_Backtracking(nums, k, sum);
    }
};