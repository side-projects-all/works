/*
Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).

 

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: [[3],[20,9],[15,7]]

Example 2:

Input: root = [1]
Output: [[1]]

Example 3:

Input: root = []
Output: []

 

Constraints:

    The number of nodes in the tree is in the range [0, 2000].
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        std::vector<std::vector<int>> ans;
        //corner case
        if (root == nullptr) {
            return ans;
        }

        ans.push_back({root->val});
        if (root->left == nullptr && root->right == nullptr) {
            return ans;
        }


        std::queue<TreeNode*> q;
        if (root->left != nullptr) {
            q.push(root->left);
        }
        if (root->right != nullptr) {
            q.push(root->right);
        }
        
        bool l_to_r = false;

        while (!q.empty()) {
            int len = q.size();

            std::vector<int> tmp(len, 0);
            for (int i = 0; i < len; ++i) {
                TreeNode* n = q.front();
                tmp[i] = n->val;
                q.pop();

                if (n->left != nullptr) {
                    q.push(n->left);
                }

                if (n->right != nullptr) {
                    q.push(n->right);
                }
            }

            if (!l_to_r) {
                std::reverse(tmp.begin(), tmp.end());
            }

            l_to_r = !l_to_r;
            ans.push_back(tmp);
        }

        return ans;
    }
};