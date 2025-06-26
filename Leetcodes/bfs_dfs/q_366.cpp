/*
Given the root of a binary tree, collect a tree's nodes as if you were doing this:

    Collect all the leaf nodes.
    Remove all the leaf nodes.
    Repeat until the tree is empty.

 

Example 1:

Input: root = [1,2,3,4,5]
Output: [[4,5,3],[2],[1]]
Explanation:
[[3,5,4],[2],[1]] and [[3,4,5],[2],[1]] are also considered correct answers since per each level it does not matter the order on which elements are returned.

Example 2:

Input: root = [1]
Output: [[1]]

 

Constraints:

    The number of nodes in the tree is in the range [1, 100].
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
    int dfs(TreeNode* root, std::vector<std::vector<int>>& ans) {
        if (root == nullptr) {
            return -1;
        }

        int left_h = dfs(root->left, ans);
        int right_h = dfs(root->right, ans);
        int h = std::max(left_h, right_h) + 1;

        if (ans.size() == h) {
            ans.push_back({});
        }

        ans[h].push_back(root->val);
        return h;
    }
    vector<vector<int>> by_dfs(TreeNode* root) {
        std::vector<std::vector<int>> ans;
        dfs(root, ans);

        return ans;
    }
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        return by_dfs(root);
    }
};