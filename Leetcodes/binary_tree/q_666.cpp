/*
If the depth of a tree is smaller than 5, then this tree can be represented by an array of three-digit integers. For each integer in this array:

    The hundreds digit represents the depth d of this node where 1 <= d <= 4.
    The tens digit represents the position p of this node in the level it belongs to where 1 <= p <= 8. The position is the same as that in a full binary tree.
    The units digit represents the value v of this node where 0 <= v <= 9.

Given an array of ascending three-digit integers nums representing a binary tree with a depth smaller than 5, return the sum of all paths from the root towards the leaves.

It is guaranteed that the given array represents a valid connected binary tree.

 

Example 1:

Input: nums = [113,215,221]
Output: 12
Explanation: The tree that the list represents is shown.
The path sum is (3 + 5) + (3 + 1) = 12.

Example 2:

Input: nums = [113,221]
Output: 4
Explanation: The tree that the list represents is shown. 
The path sum is (3 + 1) = 4.

 

Constraints:

    1 <= nums.length <= 15
    110 <= nums[i] <= 489
    nums represents a valid binary tree with depth less than 5.
    nums is sorted in ascending order.


*/

class Solution {
public:
    int pathSum(vector<int>& nums) {
        
        std::unordered_map<int, int> m;
        for (int v : nums) {
            int pos = v / 10;
            int val = v % 10;
            m[pos] = val;
        }

        int ans = 0;
        dfs_by_map(nums[0] / 10, ans, 0, m);

        return ans;
    }
private:
    void dfs_by_map(int pos, int& ans, int pre_sum, std::unordered_map<int, int>& m) {

        int level = pos / 10;
        int now = pos % 10;

        int left = (level + 1) * 10 + now * 2 - 1;
        int right = (level + 1) * 10 + now * 2;
        int sum_now = pre_sum + m[pos];

        if (!m.count(left) && !m.count(right)) {
            ans += sum_now;
            return;
        }

        if (m.count(left)) {
            dfs_by_map(left, ans, sum_now, m);
        }

        if (m.count(right)) {
            dfs_by_map(right, ans, sum_now, m);
        }
    }
};