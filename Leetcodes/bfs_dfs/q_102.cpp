/*
Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).

 

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]

Example 2:

Input: root = [1]
Output: [[1]]

Example 3:

Input: root = []
Output: []

 

Constraints:

    The number of nodes in the tree is in the range [0, 2000].
    -1000 <= Node.val <= 1000


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
    vector<vector<int>> levelOrder(TreeNode* root) {
        std::vector<std::vector<int>> result;
        if (root == NULL) {
            return result;
        }

        std::vector<int> level_nodes;
        std::queue<TreeNode*> q;
        TreeNode* now = NULL;

        q.push(root);
        int level_len = 1;
        while (!q.empty()) {
            
            level_nodes.clear();
            //the most important part is using the level_len to limit nodes that used in one level
            level_len = q.size();
            for (int i = 0; i < level_len; ++i) {
                now = q.front();
                q.pop();
                level_nodes.push_back(now->val);

                if (now->left != NULL) {
                    q.push(now->left);
                }

                if (now->right != NULL) {
                    q.push(now->right);
                }
                
            }

            result.push_back(level_nodes);
        }

        return result;
    }
};