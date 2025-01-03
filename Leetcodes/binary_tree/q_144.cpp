/*
Given the root of a binary tree, return the preorder traversal of its nodes' values.

 

Example 1:

Input: root = [1,null,2,3]
Output: [1,2,3]

Example 2:

Input: root = []
Output: []

Example 3:

Input: root = [1]
Output: [1]

 

Constraints:

    The number of nodes in the tree is in the range [0, 100].
    -100 <= Node.val <= 100


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
    vector<int> preorderTraversal(TreeNode* root) {
        std::vector<int> result;
        
        if (root == NULL) {
            return result;
        }
        std::stack<TreeNode*> pre;
        pre.push(root);
        TreeNode* curr;
        int c_val = 0;

        while(!pre.empty()) {
            curr = pre.top();

            //pop out self
            pre.pop();

            c_val = curr->val;
            
            //store value first
            result.push_back(c_val);

            //put into stack from right to left
            if (curr->right != NULL) {
                pre.push(curr->right);
            }
            
            if (curr->left != NULL) {
                pre.push(curr->left);
            }
            
        }

        return result;
    }
};