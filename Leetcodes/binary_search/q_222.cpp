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
    int depth(TreeNode* root) {
        TreeNode* b = root;
        int d = 0;
        while (b->left != nullptr) {
            ++d;
            b = b->left;
        }

        return d;
    }

    bool find_node_by_binary_search(int node_cnt, int& depth, TreeNode* root) {
        //represent the count of leaves
        int left = 0;
        int right = std::pow(2, depth) - 1; //because it is not full, we reduce 1 for max leaves
        TreeNode* b = root;

        for (int i = 0; i < depth; ++i) {
            int mid = left + (right - left) / 2;

            if (node_cnt <= mid) {
                b = b->left;
                right = mid;

            } else {
                b = b->right;
                left = mid + 1;
            }
        }

        return b != nullptr;
    }
public:
    int countNodes(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        if (root->left == nullptr && root->right == nullptr) {
            return 1;
        }

        int d = depth(root);    //depth starting from 0
        //left, right means counts of last level nodes
        int left = 1;               
        int right = std::pow(2, d) - 1; //because it were not full tree, the max is 2^h - 1

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (find_node_by_binary_search(mid, d, root)) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return std::pow(2, d) - 1 + left;
    }
};