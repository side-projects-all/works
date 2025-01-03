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
    int search(TreeNode* root, double target, double minDistance, int minVal) {
        if (root == nullptr) {
            return minVal;
        }

        double distance = std::abs(root->val - target);
        if (distance < minDistance) {
           minVal = root->val;
           minDistance = distance;
        } else if (distance == minDistance && minVal > root->val) {
            minVal = root->val;
        }

        if (target < root->val) {
            return search(root->left, target, minDistance, minVal);
        }

        return search(root->right, target, minDistance, minVal);
    }
public:
    int closestValue(TreeNode* root, double target) {
        double min = std::numeric_limits<double>::max();

        return search(root, target, min, root->val);
    }
};