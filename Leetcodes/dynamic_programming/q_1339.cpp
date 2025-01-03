/*
Given the root of a binary tree, split the binary tree into two subtrees by removing one edge such that the product of the sums of the subtrees is maximized.

Return the maximum product of the sums of the two subtrees. Since the answer may be too large, return it modulo 109 + 7.

Note that you need to maximize the answer before taking the mod and not after taking it.

 

Example 1:

Input: root = [1,2,3,4,5,6]
Output: 110
Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10. Their product is 110 (11*10)

Example 2:

Input: root = [1,null,2,3,4,null,null,5,6]
Output: 90
Explanation: Remove the red edge and get 2 binary trees with sum 15 and 6.Their product is 90 (15*6)

 

Constraints:

    The number of nodes in the tree is in the range [2, 5 * 10^4].
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
private:
    int recursive(TreeNode* root) {

        std::function<void(TreeNode*, long&)> dfs = [&](TreeNode* now, long& sum) {
            if (now == nullptr) {
                return;
            }

            dfs(now->left, sum);
            dfs(now->right, sum);

            sum += now->val;
        };

        long total = 0;
        dfs(root, total);
        long max_sum = 0;
        std::function<int(TreeNode*, long&, long&)> dfsMax = [&](TreeNode* now, long& total, long& maxSum) -> int {
            if (now == nullptr) {
                return 0;
            }

            int leftSum = dfsMax(now->left, total, maxSum);
            int rightSum = dfsMax(now->right, total, maxSum);
            long val = now->val + leftSum + rightSum;

            maxSum = std::max(maxSum, (total - val) * val);
            return val;
        };
        
        dfsMax(root, total, max_sum);

        return max_sum % 1000000007;
    }
public:
    int maxProduct(TreeNode* root) {
        return recursive(root);
    }
};