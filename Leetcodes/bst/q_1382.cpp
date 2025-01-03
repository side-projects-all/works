/*

Given the root of a binary search tree, return a balanced binary search tree with the same node values. If there is more than one answer, return any of them.

A binary search tree is balanced if the depth of the two subtrees of every node never differs by more than 1.

 

Example 1:

Input: root = [1,null,2,null,3,null,4,null,null]
Output: [2,1,3,null,null,null,4]
Explanation: This is not the only correct answer, [3,1,4,null,2] is also correct.

Example 2:

Input: root = [2,1,3]
Output: [2,1,3]

 

Constraints:

    The number of nodes in the tree is in the range [1, 10^4].
    1 <= Node.val <= 10^5


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
    void inorder(TreeNode* root, std::vector<int>& sorted) {
        if (root == nullptr) {
            return;
        }

        inorder(root->left, sorted);
        sorted.push_back(root->val);
        inorder(root->right, sorted);
    }

    TreeNode* balanced(const std::vector<int>& sorted, int b, int e) {
        if (b > e) {
            return nullptr;
        }

        int mid = b + (e - b) / 2;

        TreeNode* left_sub = balanced(sorted, b, mid - 1);
        TreeNode* right_sub = balanced(sorted, mid + 1, e);

        return new TreeNode(sorted[mid], left_sub, right_sub);
    }

public:
    TreeNode* balanceBST(TreeNode* root) {
        std::vector<int> sorted;
        inorder(root, sorted);

        return balanced(sorted, 0, sorted.size() - 1);
    }
};