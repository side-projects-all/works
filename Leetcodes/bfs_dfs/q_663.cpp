/*
Given the root of a binary tree, return true if you can partition the tree into two trees with equal sums of values after removing exactly one edge on the original tree.

 

Example 1:

Input: root = [5,10,10,null,null,2,3]
Output: true

Example 2:

Input: root = [1,2,10,null,null,2,20]
Output: false
Explanation: You cannot split the tree into two trees with equal sums after removing exactly one edge on the tree.

 

Constraints:

    The number of nodes in the tree is in the range [1, 10^4].
    -10^5 <= Node.val <= 10^5


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
    int dfs(TreeNode* root, std::stack<int>& stack) {
        if (root == nullptr) {
            return 0;
        }

        int sum = dfs(root->left, stack) + dfs(root->right, stack) + root->val;
        stack.push(sum) ;
        return stack.top();
    }
    bool by_dfs(TreeNode* root) {

        std::stack<int> stack;
        int sum = dfs(root, stack);
        stack.pop();

        if (sum % 2 == 0) {
            while (!stack.empty()) {
                if (stack.top() == sum / 2) {
                    return true;
                }

                stack.pop();
            }
        }

        return false;
    }
public:
    bool checkEqualTree(TreeNode* root) {
        return by_dfs(root);
    }
};