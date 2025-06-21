/*
Given the root of a binary tree, return the vertical order traversal of its nodes' values. (i.e., from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right.

 

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: [[9],[3,15],[20],[7]]

Example 2:

Input: root = [3,9,8,4,0,1,7]
Output: [[4],[9],[3,0,1],[8],[7]]

Example 3:

Input: root = [3,9,8,4,0,1,7,null,null,null,2,5]
Output: [[4],[9,5],[3,0,1],[8,2],[7]]

 

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
    vector<vector<int>> by_bfs(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }

        if (root->left == nullptr && root->right == nullptr) {
            return {{root->val}};
        }

        std::unordered_map<int, std::vector<int>> col_nodes;
        std::queue<std::pair<TreeNode*, int>> q;    //Node, col
        q.push({root, 0});
        int min_col = INT_MAX;
        int max_col = INT_MIN;

        while (!q.empty()) {
            auto[n, col] = q.front();
            q.pop();
            col_nodes[col].push_back(n->val);
            
            min_col = std::min(min_col, col);
            max_col = std::max(max_col, col);

            if (n->left != nullptr) {
                q.push({n->left, col - 1});
            }

            if (n->right != nullptr) {
                q.push({n->right, col + 1});
            }
        }

        std::vector<std::vector<int>> ans(max_col - min_col + 1);
        for (int i = min_col, j = 0; i <= max_col; ++i, ++j) {
            ans[j] = std::move(col_nodes[i]);
        }

        return ans;
    }
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        return by_bfs(root);
    }
};