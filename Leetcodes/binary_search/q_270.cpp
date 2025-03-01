/*
Given the root of a binary search tree and a target value, return the value in the BST that is closest to the target. If there are multiple answers, print the smallest.

 

Example 1:

Input: root = [4,2,5,1,3], target = 3.714286
Output: 4

Example 2:

Input: root = [1], target = 4.428571
Output: 1

 

Constraints:

    The number of nodes in the tree is in the range [1, 10^4].
    0 <= Node.val <= 10^9
    -10^9 <= target <= 10^9


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
    void dfs_preorder(TreeNode* root, double& target, double& min_diff, int& min_closest) {
        if (root == nullptr) {
            return;
        }

        double diff = std::abs(target - root->val);
        if (diff < min_diff) {
            min_diff = diff;
            min_closest = root->val;

        } else if (diff == min_diff && min_closest > root->val) {
            min_closest = root->val;
        }

        if (target > root->val) {
            dfs_preorder(root->right, target, min_diff, min_closest);
        } else {
            dfs_preorder(root->left, target, min_diff, min_closest);
        }
    }
public:
    int closestValue(TreeNode* root, double target) {
        double min_diff = INT_MAX;
        int min_closest = INT_MAX;
        dfs_preorder(root, target, min_diff, min_closest);

        return min_closest;
    }
};