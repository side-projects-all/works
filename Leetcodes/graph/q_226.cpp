/*
Given the root of a binary tree, invert the tree, and return its root.

 

Example 1:

Input: root = [4,2,7,1,3,6,9]
Output: [4,7,2,9,6,3,1]

Example 2:

Input: root = [2,1,3]
Output: [2,3,1]

Example 3:

Input: root = []
Output: []

 

Constraints:

    The number of nodes in the tree is in the range [0, 100].
    -100 <= Node.val <= 100


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
    TreeNode* dfs_iterative(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }

        std::stack<TreeNode*> s;
        s.push(root);

        while (!s.empty()) {
            TreeNode* n = s.top();
            s.pop();

            if (n == nullptr) {
                continue;
            }

            s.push(n->right);
            s.push(n->left);

            TreeNode* tmp = n->left;
            n->left = n->right;
            n->right = tmp;
        }

        return root;
    }

    void dfs_recurisve(TreeNode* root) {
        if (root == nullptr) {
            return;
        }

        dfs_recurisve(root->left);
        dfs_recurisve(root->right);

        TreeNode* tmp = root->left;
        root->left = root->right;
        root->right = tmp;
    }
public:
    TreeNode* invertTree(TreeNode* root) {

        //dfs_recurisve(root);
        //return root;
        return dfs_iterative(root);
    }
};