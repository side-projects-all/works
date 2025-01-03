/*
Given the root of a binary search tree, rearrange the tree in in-order so that the leftmost node in the tree is now the root of the tree, and every node has no left child and only one right child.

 

Example 1:

Input: root = [5,3,6,2,4,null,8,1,null,null,null,7,9]
Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]

Example 2:

Input: root = [5,1,7]
Output: [1,null,5,null,7]

 

Constraints:

    The number of nodes in the given tree will be in the range [1, 100].
    0 <= Node.val <= 1000


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
    void dfs_inorder(TreeNode* root, TreeNode*& newCurr) {
        if (root == nullptr) {
            return;
        }

        dfs_inorder(root->left, newCurr);

        root->left = nullptr;
        newCurr->right = root;
        newCurr = root;  

        dfs_inorder(root->right, newCurr);
    }
public:
    TreeNode* increasingBST(TreeNode* root) {
        TreeNode* newRoot = new TreeNode(0);

        //the tricky part is here, in the beginning, newRoot and newCurr point to the same address, 
        //then while in the recursion, only newCurr would continue to move!!!
        TreeNode* newCurr;
        newCurr = newRoot;
        
        dfs_inorder(root, newCurr);

        return newRoot->right;
    }
};