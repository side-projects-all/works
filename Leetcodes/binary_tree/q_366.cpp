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
    int recursive(TreeNode* root, vector<vector<int>>& result) {
        if (root == nullptr) {
            return -1;
        }
       
        int left_h = recursive(root->left, result);
        int right_h = recursive(root->right, result);

        int h = std::max(left_h, right_h) + 1;

        if (h == result.size()){
            result.push_back({});
        }

        result[h].push_back(root->val);
        return h;
    }
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        vector<vector<int>> result;

        recursive(root, result);
        return result;
    }
};