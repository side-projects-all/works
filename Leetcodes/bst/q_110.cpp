/*
Given a binary tree, determine if it is
height-balanced
.

 

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: true

Example 2:

Input: root = [1,2,2,3,3,null,null,4,4]
Output: false

Example 3:

Input: root = []
Output: true

 

Constraints:

    The number of nodes in the tree is in the range [0, 5000].
    -10^4 <= Node.val <= 10^4


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
    int height(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        return 1 + std::max(height(root->left), height(root->right));
    }

public:
    bool isBalanced(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }

        //put height check first
        //it could make recursion end faster if any imbalance existed
        int left = height(root->left);
        int right = height(root->right);

        if (std::abs(left - right) > 1) {
            return false;
        }

        if (!isBalanced(root->left)) {
            return false;
        }

        if (!isBalanced(root->right)) {
            return false;
        }

        return true;
    }
};

