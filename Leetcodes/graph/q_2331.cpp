/*

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
    
    bool dfs_recursive_postorder(TreeNode* root) {
        //a leaf node
        if (root->val < 2) {
            return (root->val == 0) ? false : true;
        }

        if (root->val == 2) {
            return (dfs_recursive_postorder(root->left) || dfs_recursive_postorder(root->right));
        }

        return (dfs_recursive_postorder(root->left) && dfs_recursive_postorder(root->right));
    }
public:
    bool evaluateTree(TreeNode* root) {

        //how to do in iterative way?
        return dfs_recursive_postorder(root);
    }
};