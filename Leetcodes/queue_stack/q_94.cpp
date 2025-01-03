/*
Given the root of a binary tree, return the inorder traversal of its nodes' values.

 

Example 1:

Input: root = [1,null,2,3]
Output: [1,3,2]

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

/*
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
/*
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
    vector<int> inorderTraversal(TreeNode* root) {
        //using morris inorderTraversal
        std::vector<int> result;
        TreeNode* now = NULL;
        TreeNode* pre = NULL;
        TreeNode* tmp = NULL;

        now = root;
        while(now != NULL) {
            if (now->left == NULL) {
                result.push_back(now->val);
                now = now->right;

            } else {
                pre = now->left;
                while(pre->right != NULL) {
                    pre = pre->right;
                }

                pre->right = now;
                tmp = now;
                now = tmp->left;
                tmp->left = NULL;

            }
        }

        return result;

        /*
        std::vector<TreeNode*> stack;
        stack.push_back(root);
        
        TreeNode* top = NULL;
        while (!stack.empty()) {
            top = stack.back();
            
            //push the left child and make the left child NULL as visited
            if (top->left != NULL) {
                stack.push_back(top->left);
                top->left = NULL;
                continue;
            }
            
            //put the value of node now into vector
            inorder.push_back(top->val);
            stack.pop_back();
            
            //push the right child and make the right child NULL as visited
            if (top->right != NULL) {
                stack.push_back(top->right);
                top->right = NULL;
                continue;
            }
        }*/
        
        //return inorder;
    }
};