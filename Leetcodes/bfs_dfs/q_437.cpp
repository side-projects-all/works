/*
Given the root of a binary tree and an integer targetSum, return the number of paths where the sum of the values along the path equals targetSum.

The path does not need to start or end at the root or a leaf, but it must go downwards (i.e., traveling only from parent nodes to child nodes).

 

Example 1:

Input: root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
Output: 3
Explanation: The paths that sum to 8 are shown.

Example 2:

Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
Output: 3

 

Constraints:

    The number of nodes in the tree is in the range [0, 1000].
    -10^9 <= Node.val <= 10^9
    -1000 <= targetSum <= 1000


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
    void dfs(TreeNode* root, int& targetSum, std::unordered_map<long, int>& m, int& cnt, long curr_sum) {
        if (root == nullptr) {
            return;
        }

        curr_sum += root->val;
        
        if (curr_sum == targetSum) {
            ++cnt;
        }

        if (m.find(curr_sum - targetSum) != m.end()) {
            cnt += m[curr_sum - targetSum];
        }

        m[curr_sum] += 1;

        dfs(root->left, targetSum, m, cnt, curr_sum);
        dfs(root->right, targetSum, m, cnt, curr_sum);

        m[curr_sum] -= 1;
    }
    int by_dfs(TreeNode* root, int& targetSum) {
        std::unordered_map<long, int> m;
        int cnt = 0;
        dfs(root, targetSum, m, cnt, 0);

        return cnt;
    }
public:
    int pathSum(TreeNode* root, int targetSum) {
        return by_dfs(root, targetSum);
    }
};
