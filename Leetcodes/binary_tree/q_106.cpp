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
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        pOrder = postorder;
        iOrder = inorder;

        now = pOrder.size() - 1;

        int i = 0;
        for (auto val : iOrder) {
            iOrderMap.insert(std::make_pair(val, i));
            ++i;
        }

        return reform(0, now);
    }

private:
    int now;
    std::vector<int> pOrder;
    std::vector<int> iOrder;
    std::unordered_map<int, int> iOrderMap;

    TreeNode* reform(int left, int right) {
        if (left > right) {
            return NULL;
        }

        int root_val = pOrder[now];
        TreeNode* root = new TreeNode(root_val);

        int index = iOrderMap[root_val];

        --now;

        root->right = reform(index + 1, right);
        root->left = reform(left, index - 1);

        return root;
    }

};