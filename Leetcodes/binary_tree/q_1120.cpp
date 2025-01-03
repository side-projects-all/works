/*
Given the root of a binary tree, return the maximum average value of a subtree of that tree. Answers within 10-5 of the actual answer will be accepted.

A subtree of a tree is any node of that tree plus all its descendants.

The average value of a tree is the sum of its values, divided by the number of nodes.

 

Example 1:

Input: root = [5,6,1]
Output: 6.00000
Explanation: 
For the node with value = 5 we have an average of (5 + 6 + 1) / 3 = 4.
For the node with value = 6 we have an average of 6 / 1 = 6.
For the node with value = 1 we have an average of 1 / 1 = 1.
So the answer is 6 which is the maximum.

Example 2:

Input: root = [0,null,1]
Output: 1.00000

 

Constraints:

    The number of nodes in the tree is in the range [1, 10^4].
    0 <= Node.val <= 10^5


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
    struct State {
        int nodeCnt = 0;
        int valSum = 0;
        double maxAvg = 0.0;
    };

    State postorder(TreeNode* root) {
        
        //reach leaf
        if (root->left == nullptr && root->right == nullptr) {
            return {1, root->val, root->val / 1.0};
        }

        State left = {0, 0, 0};
        if (root->left != nullptr) {
            left = postorder(root->left);
        }
        
        State right = {0, 0, 0};
        if (root->right != nullptr) {
            right = postorder(root->right);
        }

        int nodeCnt = left.nodeCnt + right.nodeCnt + 1;
        int nodeSum = left.valSum + right.valSum + root->val;

        double avg  = std::max((1.0 * (nodeSum)) / nodeCnt, std::max(left.maxAvg, right.maxAvg));

        return {nodeCnt, nodeSum, avg};
    }
public:
    double maximumAverageSubtree(TreeNode* root) {
        return postorder(root).maxAvg;
    }
};