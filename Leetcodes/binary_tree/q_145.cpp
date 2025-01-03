/*
Given the root of a binary tree, return the postorder traversal of its nodes' values.

 

Example 1:

Input: root = [1,null,2,3]
Output: [3,2,1]

Example 2:

Input: root = []
Output: []

Example 3:

Input: root = [1]
Output: [1]

 

Constraints:

    The number of the nodes in the tree is in the range [0, 100].
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
    vector<int> postorderTraversal(TreeNode* root) {
        std::vector<int> result;
        std::stack<TreeNode*> s;

        TreeNode* now = NULL;
        TreeNode* pre = NULL;
        TreeNode* tmp = NULL;
        now = root;
        while (now != NULL || !s.empty()) {
            
            //just another way to represent recursive function
            if (now != NULL) {
                //keep going to left child
                s.push(now);
                now = now->left;
            } else {
                //find left child is null
                //so back to parent, and try to visit right child of parent

                tmp = s.top();
                if (tmp->right != NULL && pre != tmp->right) {  //pre != tmp->right to prevent infinite loop
                    now = tmp->right;

                } else {
                    //when right child is also null or visited
                    //push back to result, and pop out this parent
                    result.push_back(tmp->val);
                    pre = tmp;
                    s.pop();
                }
                tmp = NULL;
            }

        }

        return result;
    }
};