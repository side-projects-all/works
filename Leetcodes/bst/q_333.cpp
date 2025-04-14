/*
Given the root of a binary tree, find the largest
subtree
, which is also a Binary Search Tree (BST), where the largest means subtree has the largest number of nodes.

A Binary Search Tree (BST) is a tree in which all the nodes follow the below-mentioned properties:

    The left subtree values are less than the value of their parent (root) node's value.
    The right subtree values are greater than the value of their parent (root) node's value.

Note: A subtree must include all of its descendants.

 

Example 1:

Input: root = [10,5,15,1,8,null,7]
Output: 3
Explanation: The Largest BST Subtree in this case is the highlighted one. The return value is the subtree's size, which is 3.

Example 2:

Input: root = [4,2,7,2,3,5,null,2,null,null,null,null,null,1]
Output: 2

 

Constraints:

    The number of nodes in the tree is in the range [0, 104].
    -104 <= Node.val <= 104

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
    struct Node_info {
        int min_node{ INT_MAX };
        int max_node{ INT_MIN };
        int cnts{ 0 };
    };

    Node_info post_order(TreeNode* root) {
        if (root == nullptr) {
            return {INT_MAX, INT_MIN, 0};
        }

        Node_info left = post_order(root->left);
        Node_info right = post_order(root->right);

        if (left.max_node < root->val && right.min_node > root->val) {
            return {std::min(left.min_node, root->val), std::max(right.max_node, root->val), 1 + left.cnts + right.cnts};
        }

        return {INT_MIN, INT_MAX, std::max(left.cnts, right.cnts)};
    }
public:
    int largestBSTSubtree(TreeNode* root) {
        Node_info n = post_order(root);

        return n.cnts;
    }
};