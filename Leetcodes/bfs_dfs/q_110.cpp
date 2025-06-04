/*
Given a binary tree, determine if it is

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
    int max_height(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        return 1 + std::max(max_height(root->left), max_height(root->right));
    }

    bool dfs(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }

        int diff = std::abs(max_height(root->left) - max_height(root->right));
        if (diff > 1) {
            return false;
        }

        if (!dfs(root->left)) {
            return false;
        }

        if (!dfs(root->right)) {
            return false;
        }

        return true;
    }
    bool by_dfs(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }

        return dfs(root);
    }
public:
    bool isBalanced(TreeNode* root) {
        return by_dfs(root);
    }
};