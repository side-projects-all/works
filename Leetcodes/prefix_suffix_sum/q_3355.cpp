/*
You are given an integer array nums of length n and a 2D array queries, where queries[i] = [li, ri].

For each queries[i]:

    Select a 

    of indices within the range [li, ri] in nums.
    Decrement the values at the selected indices by 1.

A Zero Array is an array where all elements are equal to 0.

Return true if it is possible to transform nums into a Zero Array after processing all the queries sequentially, otherwise return false.

 

Example 1:

Input: nums = [1,0,1], queries = [[0,2]]

Output: true

Explanation:

    For i = 0:
        Select the subset of indices as [0, 2] and decrement the values at these indices by 1.
        The array will become [0, 0, 0], which is a Zero Array.

Example 2:

Input: nums = [4,3,2,1], queries = [[1,3],[0,2]]

Output: false

Explanation:

    For i = 0:
        Select the subset of indices as [1, 2, 3] and decrement the values at these indices by 1.
        The array will become [4, 2, 1, 0].
    For i = 1:
        Select the subset of indices as [0, 1, 2] and decrement the values at these indices by 1.
        The array will become [3, 1, 0, 0], which is not a Zero Array.

 

Constraints:

    1 <= nums.length <= 10^5
    0 <= nums[i] <= 10^5
    1 <= queries.length <= 10^5
    queries[i].length == 2
    0 <= li <= ri < nums.length

*/

class Solution {
private:
    bool by_diffArr_prefixsum(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        std::vector<int> diff(n + 1, 0);

        // record the range updates by increasing one count at left index and decreasing at (right index + 1)
        for (const auto& query : queries) {
            int l = query[0];
            int r = query[1];
            diff[l] += 1;
            diff[r + 1] -= 1;
        }

        // using the idea of prefix sum to transit the same operation counts from left to right, and it will decrease when out of the range, and then we can validate the transformation
        int decrement = 0;
        for (int i = 0; i < n; ++i) {
            decrement += diff[i];
            if (decrement < nums[i]) {
                return false;
            }
        }

        return true;
    }
public:
    bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        return by_diffArr_prefixsum(nums, queries);
    }
};