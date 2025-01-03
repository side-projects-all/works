/*
Given the roots of two binary search trees, root1 and root2, return true if and only if there is a node in the first tree and a node in the second tree whose values sum up to a given integer target.

 

Example 1:

Input: root1 = [2,1,4], root2 = [1,0,3], target = 5
Output: true
Explanation: 2 and 3 sum up to 5.

Example 2:

Input: root1 = [0,-10,10], root2 = [5,1,7,0,2], target = 18
Output: false

 

Constraints:

    The number of nodes in each tree is in the range [1, 5000].
    -10^9 <= Node.val, target <= 10^9


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
    bool dfs(TreeNode* root2, int target) {
        if (root2 == nullptr) {
            return false;
        }

        if (root2->val == target) {
            return true;
        }

        bool result = false;
        if (target > root2->val && root2->right != nullptr) {
            result = dfs(root2->right, target);
        } else if (target < root2->val && root2->left != nullptr) {
            result = dfs(root2->left, target);
        }

        return result;
    }

    bool bfs(TreeNode* root1, TreeNode* root2, int target) {

        std::queue<TreeNode*> q;

        q.push(root1);

        while (!q.empty()) {
            TreeNode* n = q.front();
            q.pop();

            int rest = target - n->val;
            bool result = dfs(root2, rest);

            if (result) {
                return true;
            }

            if (n->left != nullptr) {
                q.push(n->left);
            }

            if (n->right != nullptr) {
                q.push(n->right);
            }
        }

        return false;
    }
public:
    bool twoSumBSTs(TreeNode* root1, TreeNode* root2, int target) {
        return bfs(root1, root2, target);
    }
};