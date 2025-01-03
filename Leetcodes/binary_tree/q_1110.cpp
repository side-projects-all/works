/*
Given the root of a binary tree, each node in the tree has a distinct value.

After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).

Return the roots of the trees in the remaining forest. You may return the result in any order.

 

Example 1:

Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
Output: [[1,2,null,4],[6],[7]]

Example 2:

Input: root = [1,2,4,null,3], to_delete = [3]
Output: [[1,2,4]]

 

Constraints:

    The number of nodes in the given tree is at most 1000.
    Each node has a distinct value between 1 and 1000.
    to_delete.length <= 1000
    to_delete contains distinct values between 1 and 1000.


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
    TreeNode* postorder(TreeNode* now, std::unordered_set<int>& to_del, std::vector<TreeNode*>& ans) {

        if (!now) {
            return nullptr;
        }

        now->left = postorder(now->left, to_del, ans);
        now->right = postorder(now->right, to_del, ans);

        if (to_del.find(now->val) != to_del.end()) {
            if (now->left) {
                ans.push_back(now->left);
            }

            if (now->right) {
                ans.push_back(now->right);
            }

            delete now;
            return nullptr;
        }

        return now;
    }
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        std::unordered_set<int> to_del(to_delete.begin(), to_delete.end());
        std::vector<TreeNode*> ans;

        root = postorder(root, to_del, ans);

        if (root) {
            ans.push_back(root);
        }

        return ans;
    }
};