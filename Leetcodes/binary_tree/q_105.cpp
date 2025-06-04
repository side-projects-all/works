/*
Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree, construct and return the binary tree.

 

Example 1:

Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]

Example 2:

Input: preorder = [-1], inorder = [-1]
Output: [-1]

 

Constraints:

    1 <= preorder.length <= 3000
    inorder.length == preorder.length
    -3000 <= preorder[i], inorder[i] <= 3000
    preorder and inorder consist of unique values.
    Each value of inorder also appears in preorder.
    preorder is guaranteed to be the preorder traversal of the tree.
    inorder is guaranteed to be the inorder traversal of the tree.


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
    TreeNode* recursive(std::vector<int>& preorder, int& now, std::unordered_map<int, int>& inorder_rev, int left, int right) {
        if (left > right) {
            return nullptr;
        }

        int val = preorder[now];
        TreeNode* root = new TreeNode(val);
        int i = inorder_rev[val];
        ++now;

        root->left = recursive(preorder, now, inorder_rev, left, i - 1);
        root->right = recursive(preorder, now, inorder_rev, i + 1, right);

        return root;
    }
    TreeNode* by_recursive(std::vector<int>& preorder, std::vector<int>& inorder) {
        int n = inorder.size();
        if (n == 1) {
            return new TreeNode(preorder[0]);
        }

        std::unordered_map<int, int> inorder_rev;
        
        for (int i = 0; i < n; ++i) {
            inorder_rev[inorder[i]] = i;
        }

        int index = 0;
        return recursive(preorder, index, inorder_rev, 0, n - 1);
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return by_recursive(preorder, inorder);
    }
};