/*

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
    void inorder(TreeNode* now, int& k, int& val) {
        if (now == nullptr) {
            return;
        }

        

        

        inorder(now->left, k, val);
        
        --k;
        if (k == 0) {
            val = now->val;
            return;
        }
        
        inorder(now->right, k, val);
    }
public:
    int kthSmallest(TreeNode* root, int k) {
        int val = 0;

        inorder(root, k, val);

        return val;
    }
};