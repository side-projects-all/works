/*
You are given an integer array nums with length n.

The cost of a
subarray
nums[l..r], where 0 <= l <= r < n, is defined as:

cost(l, r) = nums[l] - nums[l + 1] + ... + nums[r] * (−1)r − l

Your task is to split nums into subarrays such that the total cost of the subarrays is maximized, ensuring each element belongs to exactly one subarray.

Formally, if nums is split into k subarrays, where k > 1, at indices i1, i2, ..., ik − 1, where 0 <= i1 < i2 < ... < ik - 1 < n - 1, then the total cost will be:

cost(0, i1) + cost(i1 + 1, i2) + ... + cost(ik − 1 + 1, n − 1)

Return an integer denoting the maximum total cost of the subarrays after splitting the array optimally.

Note: If nums is not split into subarrays, i.e. k = 1, the total cost is simply cost(0, n - 1).

 

Example 1:

Input: nums = [1,-2,3,4]

Output: 10

Explanation:

One way to maximize the total cost is by splitting [1, -2, 3, 4] into subarrays [1, -2, 3] and [4]. The total cost will be (1 + 2 + 3) + 4 = 10.

Example 2:

Input: nums = [1,-1,1,-1]

Output: 4

Explanation:

One way to maximize the total cost is by splitting [1, -1, 1, -1] into subarrays [1, -1] and [1, -1]. The total cost will be (1 + 1) + (1 + 1) = 4.

Example 3:

Input: nums = [0]

Output: 0

Explanation:

We cannot split the array further, so the answer is 0.

Example 4:

Input: nums = [1,-1]

Output: 2

Explanation:

Selecting the whole array gives a total cost of 1 + 1 = 2, which is the maximum.

 

Constraints:

    1 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9


*/

class Solution {
private:
    //int n;
    //std::vector<std::vector<long long>> mem;
    
    long long iterative(vector<int>& nums) {

        std::vector<long long> mem{ nums[0] + nums[1], nums[0] - nums[1] };

        long long first = 0;
        long long second = 0;
        for (int i = 2; i < nums.size(); ++i) {
            first = mem[0];
            second = mem[1];
            mem[0] = std::max(first, second) + nums[i];
            mem[1] = first - nums[i];
        }

        return std::max(mem[0], mem[1]);
    }

    /*
    long long recursive(vector<int>& nums, int pos, int negative) {
        if (pos >= n) {
            return 0;
        }

        if (mem[pos][negative] != -1) {
            return mem[pos][negative];
        }

        long long neg = LONG_MIN;
        long long not_neg = LONG_MIN;

        if (negative) {
            neg = (-nums[pos]) + recursive(nums, pos + 1, 0);
        }

        not_neg = nums[pos] + recursive(nums, pos + 1, 1);

        return mem[pos][negative] = std::max(neg, not_neg);
    }
    */
public:
    long long maximumTotalCost(vector<int>& nums) {
        
        if (nums.size() == 1) {
            return nums[0];
        }
        /*
        n = nums.size();
        mem.resize(n, std::vector<long long>(2, -1));
        
        return nums[0] + recursive(nums, 1, 1);
        */

        return iterative(nums);
    }
};
