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
class Solution {
private:
    struct NodeVal {
        int minNode;
        int maxNode;
        int maxSize;
    };

    NodeVal postOrder(TreeNode* root) {
        if (root == nullptr) {
            return {INT_MAX, INT_MIN, 0};
        }

        NodeVal left = postOrder(root->left);
        NodeVal right = postOrder(root->right);

        if (left.maxNode < root->val && root->val < right.minNode) {
            return {std::min(root->val, left.minNode), std::max(root->val, right.maxNode), 
                                                            (left.maxSize + right.maxSize + 1)};
        }

        return {INT_MIN, INT_MAX, std::max(left.maxSize, right.maxSize)};
    }

    int findMax(TreeNode* root) {
        if (root == nullptr) {
            return INT_MIN;
        }

        return std::max({root->val, findMax(root->left), findMax(root->right)});
    }

    int findMin(TreeNode* root) {
        if (root == nullptr) {
            return INT_MAX;
        }

        return std::min({root->val, findMin(root->left), findMin(root->right)});
    }

    int countNodes(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        return 1 + countNodes(root->left) + countNodes(root->right);
    }

    bool isValidBST(TreeNode* root, TreeNode*& prev) {
        if (root == nullptr) {
            return true;
        }

        if (!isValidBST(root->left, prev)) {
            return false;
        }

        if (prev != nullptr && prev->val >= root->val) {
            return false;
        }

        prev = root;

        return isValidBST(root->right, prev);

        /*
        int leftMax = findMax(root->left);

        if (leftMax >= root->val) {
            return false;
        }

        int rightMin = findMin(root->right);

        if (rightMin <= root->val) {
            return false;
        }

        if (isValidBST(root->left, root) && isValidBST(root->right, root)) {
            return true;
        }

        return false;
        */
    }

    int recursive(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        TreeNode* prev = nullptr;
        if (isValidBST(root, prev)) {
            return countNodes(root);
        }

        return std::max(recursive(root->right), recursive(root->left));
    }
public:
    int largestBSTSubtree(TreeNode* root) {
        //return recursive(root);

        NodeVal n = postOrder(root);

        return n.maxSize;
    }
};