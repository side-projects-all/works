/*
Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

 

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: 3

Example 2:

Input: root = [1,null,2]
Output: 2

 

Constraints:

    The number of nodes in the tree is in the range [0, 10^4].
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
    int maxDepth(TreeNode* root) {

        //return iterative(root);
        return recursive(root);
    }
private:
    int recursive(TreeNode* now) {
        if (now == NULL) {
            return 0;
        }

        int depth = 1 + std::max(recursive(now->left), recursive(now->right));

        return depth;
    }

    int iterative(TreeNode* root) {
        if (root == NULL) {
            return 0;
        }

        //using level order to calculate max depth!!!!
        std::queue<TreeNode*> q;
        q.push(root);

        int maxLayer = 0;
        int level_nodes = 0;
        TreeNode* curr = NULL;

        while (!q.empty()) {
            
            level_nodes = q.size();
            for (int i = 0; i < level_nodes; ++i) {
                curr = q.front();
                q.pop();
                if (curr->left != NULL) {
                    q.push(curr->left);
                }
                if (curr->right != NULL) {
                    q.push(curr->right);
                }
            }
            maxLayer += 1;
        }

        return maxLayer;
    }
};