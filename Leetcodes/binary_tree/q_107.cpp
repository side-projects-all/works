/*
Given the root of a binary tree, return the bottom-up level order traversal of its nodes' values. (i.e., from left to right, level by level from leaf to root).

 

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: [[15,7],[9,20],[3]]

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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }

        std::queue<TreeNode*> q;
        q.push(root);
        std::vector<std::vector<int>> ans;
        
        while (!q.empty()) {
            int len = q.size();

            std::vector<int> tmp;
            for (int i = 0; i < len; ++i) {
                TreeNode* n = q.front();
                q.pop();

                tmp.push_back(n->val);
                if (n->left != nullptr) {
                    q.push(n->left);
                }

                if (n->right != nullptr) {
                    q.push(n->right);
                }
            }

            ans.push_back(tmp);
        }

        std::reverse(ans.begin(), ans.end());

        return ans;
    }
};