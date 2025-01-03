/*
Given the root of a Binary Search Tree (BST), return the minimum difference between the values of any two different nodes in the tree.

 

Example 1:

Input: root = [4,2,6,1,3]
Output: 1

Example 2:

Input: root = [1,0,48,null,null,12,49]
Output: 1

 

Constraints:

    The number of nodes in the tree is in the range [2, 100].
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
    void dfs_inorder_nolist(TreeNode* root, TreeNode*& prev, int& min) {
        if (root == nullptr) {
            return;
        }

        dfs_inorder_nolist(root->left, prev, min);

        //because of inorder travese, we will have ascending order
        if (prev != nullptr) {
            min = std::min(min, root->val - prev->val);
        }

        prev = root;

        dfs_inorder_nolist(root->right, prev, min);

    }

    void dfs_inorder_list(TreeNode* root, std::vector<int>& list)  {

        if (root != nullptr) {
            dfs_inorder_list(root->left, list);
            
            list.push_back(root->val);

            dfs_inorder_list(root->right, list);
        }
    }
public:
    int minDiffInBST(TreeNode* root) {
        int min = 100001;

        TreeNode* now = nullptr;
        //no list
        dfs_inorder_nolist(root, now, min);

        //with list
        /*
        std::vector<int> list;

        dfs_inorder_list(root, list);
        for (int i = 1; i < list.size(); ++i) {
            min = std::min(min, std::abs(list[i] - list[i - 1]));
        }
        */
        return min;   
    }
};