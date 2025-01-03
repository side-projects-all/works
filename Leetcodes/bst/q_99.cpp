/*
You are given the root of a binary search tree (BST), where the values of exactly two nodes of the tree were swapped by mistake. Recover the tree without changing its structure.

 

Example 1:

Input: root = [1,3,null,null,2]
Output: [3,1,null,null,2]
Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.

Example 2:

Input: root = [3,1,4,null,null,2]
Output: [2,1,4,null,null,3]
Explanation: 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3 makes the BST valid.

 

Constraints:

    The number of nodes in the tree is in the range [2, 1000].
    -231 <= Node.val <= 231 - 1

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
    void dfs_inorder_iterative(TreeNode* root) {
        std::stack<TreeNode*> s;
        TreeNode* now = root;
        TreeNode* pre = nullptr;
        TreeNode* x = nullptr;
        TreeNode* y = nullptr;

        while (!s.empty() || now != nullptr) {

            //traverse left
            while (now != nullptr) {
                s.push(now);
                now = now->left;
            }
            
            now = s.top();
            s.pop();

            if (pre != nullptr && now->val < pre->val) {
                y = now;
                if (x == nullptr) {
                    x = pre;
                } else {
                    break;
                }
            }

            pre = now;

            //go right sub-tree
            now = now->right;
        }

        std::swap(x->val, y->val);
    }
    void dfs_inorder_recursive(TreeNode* root) {
        TreeNode* pre = nullptr;
        TreeNode* x = nullptr;
        TreeNode* y = nullptr;

        std::function<void(TreeNode*)> in = [&](TreeNode* now) {
            if (now == nullptr) {
                return;
            }

            in(now->left);
            if (pre != nullptr && now->val < pre->val) {
                y = now;
                if (x == nullptr) {
                    x = pre;
                } else {
                    return;
                }
            }
            pre = now;

            in(now->right);
            
            return;
        };

        in(root);

        std::swap(x->val, y->val);
    }

public:
    void recoverTree(TreeNode* root) {
        //dfs_inorder_recursive(root);
        dfs_inorder_iterative(root);
    }
};