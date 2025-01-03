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
    vector<vector<int>> byBFS(TreeNode* root) {
        std::vector<std::vector<int>> result;
        if (root == nullptr) {
            return result;
        }

        std::unordered_map<int, std::vector<int>> m;
        std::queue<std::pair<TreeNode*, int>> q;
        int col = 0;
        q.push({root, col});

        int minCol = 0;
        int maxCol = 0;

        while (!q.empty()) {
            std::pair<TreeNode*, int> p = q.front();
            q.pop();

            TreeNode* n = p.first;
            int col_now = p.second;

            if (n != nullptr) {

                m[col_now].push_back(n->val);
                minCol = std::min(minCol, col_now);
                maxCol = std::max(maxCol, col_now);

                q.push({n->left, col_now - 1});
                q.push({n->right, col_now + 1});
            }
        }
        
        for (int i = minCol; i < maxCol + 1; ++i) {
            result.push_back(m[i]);
        }

        return result;
    }
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        return byBFS(root);
    }
};