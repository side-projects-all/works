/*
Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:

    The left 

    of a node contains only nodes with keys less than the node's key.
    The right subtree of a node contains only nodes with keys greater than the node's key.
    Both the left and right subtrees must also be binary search trees.

 

Example 1:

Input: root = [2,1,3]
Output: true

Example 2:

Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.

 

Constraints:

    The number of nodes in the tree is in the range [1, 10^4].
    -2^31 <= Node.val <= 2^31 - 1

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
    bool dfs(TreeNode* root, long left_min, long right_max) {
        if (root == nullptr) {
            return true; 
        }

        if (left_min < root->val && right_max > root->val) {
            return dfs(root->left, left_min, root->val) && dfs(root->right, root->val, right_max);
        }

        return false;
    }
    bool by_dfs(TreeNode* root) {
        if (root->left == nullptr && root->right == nullptr) {
            return true;
        }

        return dfs(root, -2'200'000'000, 2'200'000'000);
    }
public:
    bool isValidBST(TreeNode* root) {
        return by_dfs(root);
    }
};