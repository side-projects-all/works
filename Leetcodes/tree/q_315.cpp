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
    vector<int> by_fenwick_tree(vector<int>& nums) {
        int offset = 1e4;
        int len = 2 * offset + 1;
        std::vector<int> tree(len);
        std::vector<int> ans;

        for (int i = nums.size() - 1; i >= 0; --i) {
            int smaller_cnt = query_val(nums[i] + offset, tree);
            ans.push_back(smaller_cnt);
            update_val(nums[i] + offset, 1, tree);
        }

        std::reverse(ans.begin(), ans.end());
        return ans;
    }

    void update_val(int i, int val, std::vector<int>& tree) {
        ++i;    //1 index started!!! remember

        while (i < tree.size()) {
            tree[i] += val;
            i += (i & -i);
        }
    }

    int query_val(int i, std::vector<int>& tree) {
        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= (i & -i);
        }

        return sum;
    }

    vector<int> by_segment_tree(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return { 0 };
        }

        int offset = 1e4;
        int len = 2 * 1e4 + 1;
        //this tree is bucket, 
        //and we use ofset to store positive and negative
        std::vector<int> tree(len * 2); 
        std::vector<int> ans;

        //travel from right to left to perform sum of smaller ones than i
        for (int i = n - 1; i >= 0; --i) {
            int smallers = segment_tree_query(0, nums[i] + offset, tree, len);
            ans.push_back(smallers);

            segment_tree_update(nums[i] + offset, 1, tree, len);
        }

        std::reverse(ans.begin(), ans.end());
        return ans;
    }

    void segment_tree_update(int i, int val, std::vector<int>& tree, int len) {
        i += len;

        tree[i] += val;

        while (i > 1) {
            i /= 2;
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
        }
    }

    int segment_tree_query(int left, int right, std::vector<int>& tree, int len) {
        int ans = 0;
        left += len;
        right += len;

        while (left < right) {
            if (left % 2 == 1) {
                ans += tree[left];
                ++left;
            }

            left /= 2;

            if (right % 2 == 1) {
                --right;
                ans += tree[right];
            }

            right /= 2;
        }

        return ans;
    }
    
public:
    vector<int> countSmaller(vector<int>& nums) {

        //return by_segment_tree(nums);
        return by_fenwick_tree(nums);
    }
};