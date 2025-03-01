/*
Given an integer array nums, return an integer array counts where counts[i] is the number of smaller elements to the right of nums[i].

 

Example 1:

Input: nums = [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.

Example 2:

Input: nums = [-1]
Output: [0]

Example 3:

Input: nums = [-1,-1]
Output: [0,0]

 

Constraints:

    1 <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4


*/

class Solution {
private:
    void update_fenwick_tree(std::vector<int>& tree, int i, int val) {
        ++i;

        while (i < tree.size()) {
            tree[i] += val;
            i += (i & -i);
        }
    }

    int query_fenwick_tree(std::vector<int>& tree, int i) {

        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= (i & -i);
        }

        return sum;
    }

    std::vector<int> by_fenwick_tree(vector<int>& nums) {
        int n = nums.size();
        int offset = 1e4;
        std::vector<int> tree(2 * offset + 1);
        std::vector<int> ans(n);
        for (int i = n - 1; i >= 0; --i) {
            ans[i] = query_fenwick_tree(tree, nums[i] + offset);
            update_fenwick_tree(tree, nums[i] + offset, 1);
        }

        return ans;
    }

    void update_segment_tree(std::vector<int>& tree, int size, int i, int val) {
        i += size;    //move to leaf index
        tree[i] += val;

        while (i > 1) {
            i /= 2;     //go to parent and update
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
        }
    }

    int query_segment_tree(std::vector<int>& tree, int size, int left, int right) {
        int sum = 0;
        left += size;
        right += size;
        while (left < right) {
            if (left % 2 == 1) {
                sum += tree[left];
                ++left;
            }

            if (right % 2 == 1) {
                --right;
                sum += tree[right];
            }

            left /= 2;
            right /= 2;
        }

        return sum;
    }

    std::vector<int> by_segment_tree(vector<int>& nums) {
        int offset = 1e4;
        int total = 2 * offset + 1;
        std::vector<int> tree(2 * total);
        int n = nums.size();
        std::vector<int> ans(n);
        for (int i = n - 1; i >= 0; --i) {
            ans[i] = query_segment_tree(tree, total, 0, nums[i] + offset);
            update_segment_tree(tree, total, nums[i] + offset, 1);
        }

        return ans;
    }
public:
    vector<int> countSmaller(vector<int>& nums) {
        //return by_fenwick_tree(nums);
        return by_segment_tree(nums);
    }
};