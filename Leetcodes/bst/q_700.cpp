/*
You are given the root of a binary search tree (BST) and an integer val.

Find the node in the BST that the node's value equals val and return the subtree rooted with that node. If such a node does not exist, return null.

 

Example 1:

Input: root = [4,2,7,1,3], val = 2
Output: [2,1,3]

Example 2:

Input: root = [4,2,7,1,3], val = 5
Output: []

 

Constraints:

    The number of nodes in the tree is in the range [1, 5000].
    1 <= Node.val <= 10^7
    root is a binary search tree.
    1 <= val <= 10^7


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
    TreeNode* recursive(TreeNode* root, int val) {
        if (root == NULL) {
            return root;
        }

        TreeNode* result = NULL;
        if (val == root->val) {
            result = root;
        } else if (val > root->val) {
            result = searchBST(root->right, val);
        } else if (val < root->val) {
            result = searchBST(root->left, val);
        }

        return result;
    }

    TreeNode* iterative(TreeNode* root, int val) {
        TreeNode* now = root;

        while (now != nullptr) {
            if (val == now->val) {
                break;
            } else if (val > now->val) {
                now = now->right;
            } else {
                now = now->left;
            }
        }

        return (now == nullptr) ? nullptr : now;
    }

public:
    TreeNode* searchBST(TreeNode* root, int val) {
        //return recursive(root, val);
        return iterative( root, val);
    }
};
