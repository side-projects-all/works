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
    bool dfs_iterative(TreeNode* root) {
        std::stack<TreeNode*> s;
        s.push(root);

        int preVal = root->val;
        while (!s.empty()) {
            TreeNode* n = s.top();
            s.pop();

            if (n != nullptr) {

                if (n->val != preVal) {
                    return false;
                }

                if (n->left != nullptr) {
                    s.push(n->left);
                }

                if (n->right != nullptr) {
                    s.push(n->right);
                }
            }
        }

        return true;
    }

    bool dfs_recursive(TreeNode* root, int preVal) {
        if (root == nullptr) {
            return true;
        }

        if (root->val != preVal) {
            return false;
        }

        bool leftSub = dfs_recursive(root->left, root->val);
        bool righSub = dfs_recursive(root->right, root->val);

        return leftSub && righSub;
    }
public:
    bool isUnivalTree(TreeNode* root) {
        //return dfs_recursive(root, root->val);

        return dfs_iterative(root);
    }
};