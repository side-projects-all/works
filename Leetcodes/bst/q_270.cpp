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
    void dfs(TreeNode* root, double& target, double& min_diff, int& closest) {
        if (root == nullptr) {
            return;
        }

        double diff = std::abs(root->val - target);
        if (diff < min_diff) {
            min_diff = diff;
            closest = root->val;

        } else if (diff == min_diff) {

            closest = std::min(closest, root->val);
        }

        if (target < root->val) {
            dfs(root->left, target, min_diff, closest);

        } else if (target > root->val) {
            dfs(root->right, target, min_diff, closest);
        }
    }
    int by_dfs(TreeNode* root, double& target) {
        double min_diff = INT_MAX;
        int closest = INT_MAX;
        dfs(root, target, min_diff, closest);

        return closest;
    }
public:
    int closestValue(TreeNode* root, double target) {
        return by_dfs(root, target);
    }
};