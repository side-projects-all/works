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
        
        //because std::set is implemented by red-black tree, a balanced tree, we use it here
        //as binary search tree
        std::multiset<int> tree;

        int j = 0;
        for (int i = 0; i < nums.size(); ++i) {
            
            //the lower bound in c++ is not less than (i.e. greater or equal to) key
            auto upper = tree.lower_bound(nums[i]);
            if (upper != tree.end()) {

                if (*upper - nums[i] <= valueDiff) {
                    return true;
                }
            }

            if (upper != tree.begin()) {
                auto lower = --upper;
                if (nums[i] - *lower <= valueDiff) {
                    return true;
                }
            }

            tree.insert(nums[i]);

            //this part keeps the sliding window size
            if (tree.size() == indexDiff + 1) {
                tree.erase(nums[j]);
                ++j;
            }
        }

        return false;
    }
};