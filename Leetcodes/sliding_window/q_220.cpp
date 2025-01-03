/*
You are given an integer array nums and two integers indexDiff and valueDiff.

Find a pair of indices (i, j) such that:

    i != j,
    abs(i - j) <= indexDiff.
    abs(nums[i] - nums[j]) <= valueDiff, and

Return true if such pair exists or false otherwise.

 

Example 1:

Input: nums = [1,2,3,1], indexDiff = 3, valueDiff = 0
Output: true
Explanation: We can choose (i, j) = (0, 3).
We satisfy the three conditions:
i != j --> 0 != 3
abs(i - j) <= indexDiff --> abs(0 - 3) <= 3
abs(nums[i] - nums[j]) <= valueDiff --> abs(1 - 1) <= 0

Example 2:

Input: nums = [1,5,9,1,5,9], indexDiff = 2, valueDiff = 3
Output: false
Explanation: After trying all the possible pairs (i, j), we cannot satisfy the three conditions, so we return false.

 

Constraints:

    2 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9
    1 <= indexDiff <= nums.length
    0 <= valueDiff <= 10^9


*/

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        return by_sliding_window(nums, indexDiff, valueDiff);
    }

private:
    long get_id(long num, long width) {
        return num < 0 ? (num + 1) / width - 1 : num / width;
    }

    bool by_sliding_window(vector<int>& nums, int& indexDiff, int& valueDiff) {
        std::unordered_map<long, long> buckets;
        long width = (long)valueDiff + 1;

        for (int i = 0; i < nums.size(); ++i) {
            long bucket = get_id(nums[i], width);

            if (buckets.count(bucket)) {
                return true;
            }

            if (buckets.count(bucket - 1) && std::abs(nums[i] - buckets[bucket - 1]) < width) {
                return true;
            }

            if (buckets.count(bucket + 1) && std::abs(nums[i] - buckets[bucket + 1]) < width) {
                return true;
            }

            buckets[bucket] = (long)nums[i];
            if (i >= indexDiff) {
                buckets.erase(get_id(nums[i - indexDiff], width));
            }
        }

        return false;
    }
};