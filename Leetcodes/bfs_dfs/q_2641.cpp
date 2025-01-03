/*
Given the root of a binary tree, replace the value of each node in the tree with the sum of all its cousins' values.

Two nodes of a binary tree are cousins if they have the same depth with different parents.

Return the root of the modified tree.

Note that the depth of a node is the number of edges in the path from the root node to it.

 

Example 1:

Input: root = [5,4,9,1,10,null,7]
Output: [0,0,0,7,7,null,11]
Explanation: The diagram above shows the initial binary tree and the binary tree after changing the value of each node.
- Node with value 5 does not have any cousins so its sum is 0.
- Node with value 4 does not have any cousins so its sum is 0.
- Node with value 9 does not have any cousins so its sum is 0.
- Node with value 1 has a cousin with value 7 so its sum is 7.
- Node with value 10 has a cousin with value 7 so its sum is 7.
- Node with value 7 has cousins with values 1 and 10 so its sum is 11.

Example 2:

Input: root = [3,1,2]
Output: [0,0,0]
Explanation: The diagram above shows the initial binary tree and the binary tree after changing the value of each node.
- Node with value 3 does not have any cousins so its sum is 0.
- Node with value 1 does not have any cousins so its sum is 0.
- Node with value 2 does not have any cousins so its sum is 0.

 

Constraints:

    The number of nodes in the tree is in the range [1, 10^5].
    1 <= Node.val <= 10^4


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
public:
    TreeNode* replaceValueInTree(TreeNode* root) {
        return bfs_two_pass(root);
    }

private:
    TreeNode* bfs_two_pass(TreeNode* root) {
        std::queue<TreeNode*> q;
        q.push(root);
        std::vector<int> level_sums;

        //get all level sums
        while (!q.empty()) {
            int sum = 0;
            int len = q.size();
            for (int i = 0; i < len; ++i) {
                TreeNode* curr = q.front();
                q.pop();

                sum += curr->val;
                if (curr->left != nullptr) {
                    q.push(curr->left);
                }

                if (curr->right != nullptr) {
                    q.push(curr->right);
                }
            }

            level_sums.push_back(sum);
        }

        q.push(root);
        int level_i = 1;
        root->val = 0;
        while (!q.empty()) {
            int len = q.size();

            for (int i = 0; i < len; ++i) {
                TreeNode* curr = q.front();
                q.pop();

                int sibling_sum = (curr->left ? curr->left->val : 0) + (curr->right ? curr->right->val : 0);

                if (curr->left != nullptr) {
                    curr->left->val = level_sums[level_i] - sibling_sum;
                    q.push(curr->left);
                }

                if (curr->right != nullptr) {
                    curr->right->val = level_sums[level_i] - sibling_sum;
                    q.push(curr->right);
                }
            }
            ++level_i;
        }

        return root;
    }
};