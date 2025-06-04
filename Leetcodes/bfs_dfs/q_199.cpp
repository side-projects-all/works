/*
Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

 

Example 1:

Input: root = [1,2,3,null,5,null,4]
Output: [1,3,4]

Example 2:

Input: root = [1,null,3]
Output: [1,3]

Example 3:

Input: root = []
Output: []

 

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
private:
    void dfs(TreeNode* root, int level, std::vector<int>& right_most) {
        if (root == nullptr) {
            return;
        }
        if (level == right_most.size()) {
            right_most.push_back(root->val);
        }

        dfs(root->right, level + 1, right_most);
        dfs(root->left, level + 1, right_most);
    }
    vector<int> by_dfs(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }

        std::vector<int> ans;
        dfs(root, 0, ans);
        
        return ans;
    }
    vector<int> by_bfs(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }

        std::vector<int> ans;
        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int rest = q.size() - 1;
            TreeNode* right_first = q.front();
            q.pop();

            ans.push_back(right_first->val);
            if (right_first->right != nullptr) {
                q.push(right_first->right);
            }

            if (right_first->left != nullptr) {
                q.push(right_first->left);
            }

            for (int i = 0; i < rest; ++i) {
                TreeNode* node = q.front();
                q.pop();

                
                if (node->right != nullptr) {
                    q.push(node->right);
                }

                if (node->left != nullptr) {
                    q.push(node->left);
                }
            }
        }

        return ans;
    }
public:
    vector<int> rightSideView(TreeNode* root) {
        //return by_bfs(root);
        return by_dfs(root);
    }
};