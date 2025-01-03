/*
Given the root of a binary search tree and an integer k, return true if there exist two elements in the BST such that their sum is equal to k, or false otherwise.

 

Example 1:

Input: root = [5,3,6,2,4,null,7], k = 9
Output: true

Example 2:

Input: root = [5,3,6,2,4,null,7], k = 28
Output: false

 

Constraints:

    The number of nodes in the tree is in the range [1, 10^4].
    -10^4 <= Node.val <= 10^4
    root is guaranteed to be a valid binary search tree.
    -10^5 <= k <= 10^5


*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    void dfs(TreeNode* root, std::vector<int>& vals) {
        if (root != nullptr) {

            dfs(root->left, vals);
            vals.push_back(root->val);
            dfs(root->right, vals);
        }
    }
public:
    bool findTarget(TreeNode* root, int k) {
        bool result = false;
        std::vector<int> vals;

        dfs(root, vals);

        int left = 0;
        int right = vals.size() - 1;

        while (left < right) {
            int sum = vals[left] + vals[right];

            if (sum == k) {
                return true;
            }

            if (sum > k) {
                --right;
            } else {
                ++left;
            }
        }

        //my naive binary search
        /*
        for (int i = 0; i < vals.size(); ++i) {
            int target = k - vals[i];

            //do binary search
            int left = i + 1;
            int right = vals.size() - 1;

            while (left <= right) {
                int mid = left + (right - left) / 2;

                if (vals[mid] == target) {
                    return true;
                }

                if (vals[mid] > target) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
        }
        */

        return result;
    }
};