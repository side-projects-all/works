/*
Given the root of a Binary Search Tree (BST), return the minimum absolute difference between the values of any two different nodes in the tree.

 

Example 1:

Input: root = [4,2,6,1,3]
Output: 1

Example 2:

Input: root = [1,0,48,null,null,12,49]
Output: 1

 

Constraints:

    The number of nodes in the tree is in the range [2, 10^4].
    0 <= Node.val <= 10^5

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
    void dfs_inorder(TreeNode* root, TreeNode*& prev, int& min) {
        if (root == nullptr) {
            return;
        }

        dfs_inorder(root->left, prev, min);

        if (prev != nullptr) {
            min = std::min(min, root->val - prev->val);
        }

        prev = root;

        dfs_inorder(root->right, prev, min);
    }
public:
    int getMinimumDifference(TreeNode* root) {
        TreeNode* prev = nullptr;
        int min = 100001;
        dfs_inorder(root, prev, min);

        return min;
    }
};