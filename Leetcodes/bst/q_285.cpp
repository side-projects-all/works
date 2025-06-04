/*
Given the root of a binary search tree and a node p in it, return the in-order successor of that node in the BST. If the given node has no in-order successor in the tree, return null.

The successor of a node p is the node with the smallest key greater than p.val.

 

Example 1:

Input: root = [2,1,3], p = 1
Output: 2
Explanation: 1's in-order successor node is 2. Note that both p and the return value is of TreeNode type.

Example 2:

Input: root = [5,3,6,2,4,null,null,1], p = 6
Output: null
Explanation: There is no in-order successor of the current node, so the answer is null.

 

Constraints:

    The number of nodes in the tree is in the range [1, 10^4].
    -10^5 <= Node.val <= 10^5
    All Nodes will have unique values.


*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    void dfs(TreeNode* root, TreeNode* p, TreeNode*& suc, bool& found) {
        if (root == nullptr) {
            return;
        }

        dfs(root->left, p, suc, found);

        if (found) {
            suc = root;
            found = false;
            return;
        }

        if (root == p) {
            found = true;
        }

        dfs(root->right, p, suc, found);
    }
    TreeNode* by_dfs(TreeNode* root, TreeNode* p) {
        TreeNode* suc = nullptr;
        bool found = false;

        dfs(root, p, suc, found);
        return suc;
    }
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        return by_dfs(root, p);
    }
};