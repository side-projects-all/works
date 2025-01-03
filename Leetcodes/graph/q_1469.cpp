/*
In a binary tree, a lonely node is a node that is the only child of its parent node. The root of the tree is not lonely because it does not have a parent node.

Given the root of a binary tree, return an array containing the values of all lonely nodes in the tree. Return the list in any order.

 

Example 1:

Input: root = [1,2,3,null,4]
Output: [4]
Explanation: Light blue node is the only lonely node.
Node 1 is the root and is not lonely.
Nodes 2 and 3 have the same parent and are not lonely.

Example 2:

Input: root = [7,1,4,6,null,5,3,null,null,null,null,null,2]
Output: [6,2]
Explanation: Light blue nodes are lonely nodes.
Please remember that order doesn't matter, [2,6] is also an acceptable answer.

Example 3:


Input: root = [11,99,88,77,null,null,66,55,null,null,44,33,null,null,22]
Output: [77,55,33,66,44,22]
Explanation: Nodes 99 and 88 share the same parent. Node 11 is the root.
All other nodes are lonely.

 

Constraints:

    The number of nodes in the tree is in the range [1, 1000].
    1 <= Node.val <= 10^6


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
    std::vector<int> dfs_iterative(TreeNode* root) {
        std::vector<int> lonely;

        std::stack<TreeNode*> s;
        s.push(root);

        while (!s.empty()) {
            TreeNode* n = s.top();
            s.pop();

            if (n != nullptr) {

                if (n->left != nullptr) {

                    if (n->right == nullptr) {
                        lonely.push_back(n->left->val);
                    }
                    s.push(n->left);
                }

                if (n->right != nullptr) {

                    if (n->left == nullptr) {
                        lonely.push_back(n->right->val);
                    }
                    s.push(n->right);
                }
            }

        }

        return lonely;
    }

    void dfs_recursive(TreeNode* root, std::vector<int>& lonely) {
        if (root->left == nullptr && root->right == nullptr) {
            return;
        }

        if (root->left != nullptr) {

            if (root->right == nullptr) {
                lonely.push_back(root->left->val);
            }
            dfs_recursive(root->left, lonely);
        }

        if (root->right != nullptr) {

            if (root->left == nullptr) {
                lonely.push_back(root->right->val);
            }
            dfs_recursive(root->right, lonely);
        }
    }
public:
    vector<int> getLonelyNodes(TreeNode* root) {
        //corner case
        //only root
        if (root->left == nullptr && root->right == nullptr) {
            return {};
        }
        
        /*
        std::vector<int> lonely;
        dfs_recursive(root, lonely);

        return lonely;
        */
        
        return dfs_iterative(root);
    }
};