/*
Given the root of a complete binary tree, return the number of the nodes in the tree.

According to Wikipedia, every level, except possibly the last, is completely filled in a complete binary tree, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

Design an algorithm that runs in less than O(n) time complexity.

 

Example 1:

Input: root = [1,2,3,4,5,6]
Output: 6

Example 2:

Input: root = []
Output: 0

Example 3:

Input: root = [1]
Output: 1

 

Constraints:

    The number of nodes in the tree is in the range [0, 5 * 10^4].
    0 <= Node.val <= 5 * 10^4
    The tree is guaranteed to be complete.


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
    //because it is a complete tree, the minimum leaf node will be in the left sub-tree, 
    //for counting depth, we only need it.
    int depth(TreeNode* root) {
        int depth = 0;
        TreeNode* node = root;

        while (node->left != nullptr) {
            node = node->left;
            ++depth;
        }

        return depth;
    }
    //d: depth
    bool isNodeExist(int index, int d, TreeNode* node) {
        int left = 0;
        int right = (int)std::pow(2, d) - 1;
        int mid = 0;
        TreeNode* now = node;

        for (int i = 0; i < d; ++i) {
            mid = left + (right - left) / 2;

            if (index <= mid) {
                now = now->left;
                right = mid;
            } else {
                now = now->right;
                left = mid + 1;
            }
        }

        return now != nullptr;
    }

public:
    int countNodes(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        int d = depth(root);

        if (d == 0) {
            return 1;
        }

        int left = 1;
        int right = (int)std::pow(2, d) - 1;
        int mid = 0;

        while (left <= right) {
            mid = left + (right - left) / 2;

            if (isNodeExist(mid, d, root)) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return (int)std::pow(2, d) - 1 + left;
    }
};