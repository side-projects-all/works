/*
Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree and postorder is the postorder traversal of the same tree, construct and return the binary tree.

 

Example 1:

Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
Output: [3,9,20,null,null,15,7]

Example 2:

Input: inorder = [-1], postorder = [-1]
Output: [-1]

 

Constraints:

    1 <= inorder.length <= 3000
    postorder.length == inorder.length
    -3000 <= inorder[i], postorder[i] <= 3000
    inorder and postorder consist of unique values.
    Each value of postorder also appears in inorder.
    inorder is guaranteed to be the inorder traversal of the tree.
    postorder is guaranteed to be the postorder traversal of the tree.


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
    TreeNode* recursive(std::vector<int>& postorder, int& now, std::unordered_map<int, int>& inorder_rev, int left, int right) {
        if (left > right) {
            return nullptr;
        }

        int val = postorder[now];
        TreeNode* root = new TreeNode(val);
        int i = inorder_rev[val];
        --now;

        root->right = recursive(postorder, now, inorder_rev, i + 1, right);
        root->left = recursive(postorder, now, inorder_rev, left, i - 1);
        
        return root;
    }
    TreeNode* by_recursive(std::vector<int>& inorder, std::vector<int>& postorder) {
        int n = inorder.size();
        if (n == 1) {
            return new TreeNode(inorder[0]);
        }

        std::unordered_map<int, int> inorder_rev;
        for (int i = 0; i < n; ++i) {
            inorder_rev[inorder[i]] = i;
        }
        int index = n - 1;
        return recursive(postorder, index, inorder_rev, 0, n - 1);
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return by_recursive(inorder, postorder);
    }
};