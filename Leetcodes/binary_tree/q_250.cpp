/*
Given the root of a binary tree, return the number of uni-value
subtrees
.

A uni-value subtree means all nodes of the subtree have the same value.

 

Example 1:

Input: root = [5,1,5,5,5,null,5]
Output: 4

Example 2:

Input: root = []
Output: 0

Example 3:

Input: root = [5,5,5,5,5,null,5]
Output: 6

 

Constraints:

    The number of the node in the tree will be in the range [0, 1000].
    -1000 <= Node.val <= 1000


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
    bool recursive(TreeNode* root, int& cnt) {
        if (root == nullptr) {
            return true;
        }

        bool left_uni = recursive(root->left, cnt);
        bool right_uni = recursive(root->right, cnt);

        if (left_uni && right_uni) {
            if (root->left != nullptr && root->left->val != root->val) {
                return false;
            }

            if (root->right != nullptr && root->right->val != root->val) {
                return false;
            }

            ++cnt;
            return true;
        }

        return false;
    }
public:
    int countUnivalSubtrees(TreeNode* root) {
        int cnt = 0;
        recursive(root, cnt);
        return cnt;
    }
};