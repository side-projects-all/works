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
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        pre = preorder;
        in = inorder;
        now = 0;

        int index = 0;
        for (auto val : inorder) {
            inMap.insert(std::make_pair(val, index));
            ++index;
        }

        return reform(now, inorder.size() - 1);
    }

private:
    std::vector<int> pre;
    std::vector<int> in;
    int now;
    std::unordered_map<int, int> inMap;

    TreeNode* reform(int left, int right) {
        
        if (left > right) {
            return NULL;
        }

        int val = pre[now];
        TreeNode* root = new TreeNode(val);

        int index = inMap[val];
        ++now;

        //the only difference betwwen preorder and postorder
        root->left = reform(left, index - 1);
        root->right = reform(index + 1, right);

        return root;
    }
};