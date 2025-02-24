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
private:
    void dfs_inorder(TreeNode* root, std::vector<int>& vals) {
        if (root == nullptr) {
            return;
        }

        dfs_inorder(root->left, vals);
        vals.push_back(root->val);
        dfs_inorder(root->right, vals);
    }
public:
    bool findTarget(TreeNode* root, int k) {
        if (root->left == nullptr && root->right == nullptr) {
            return false;
        }

        std::vector<int> vals;
        dfs_inorder(root, vals);
        
        int left = 0;
        int right = vals.size() - 1;
        while (left < right) {
            if (vals[left] + vals[right] == k) {
                return true;
            }

            if (vals[left] + vals[right] > k) {
                --right;
            } else {
                ++left;
            }
        }

        return false;
    }
};