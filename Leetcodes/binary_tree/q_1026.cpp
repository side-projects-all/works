/*
Given the root of a binary tree, find the maximum value v for which there exist different nodes a and b where v = |a.val - b.val| and a is an ancestor of b.

A node a is an ancestor of b if either: any child of a is equal to b or any child of a is an ancestor of b.

 

Example 1:

Input: root = [8,3,10,1,6,null,14,null,null,4,7,13]
Output: 7
Explanation: We have various ancestor-node differences, some of which are given below :
|8 - 3| = 5
|3 - 7| = 4
|8 - 1| = 7
|10 - 13| = 3
Among all possible differences, the maximum value of 7 is obtained by |8 - 1| = 7.

Example 2:

Input: root = [1,null,2,null,0,3]
Output: 3

 

Constraints:

    The number of nodes in the tree is in the range [2, 5000].
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
    int dfs_better(TreeNode* root, int currMax, int currMin) {
        if (root == nullptr) {
            return currMax - currMin;
        }

        currMax = std::max(currMax, root->val);
        currMin = std::min(currMin, root->val);

        int left = dfs_better(root->left, currMax, currMin);
        int right = dfs_better(root->right, currMax, currMin);

        return std::max(left, right);
    }
    std::pair<int, int> dfs_naive(TreeNode* root, int& maxDiff) {
        if (root == nullptr) {
            return {-1, 100001};
        }

        if (root->left == nullptr && root->right == nullptr) {
            return {root->val, root->val};
        }

        std::pair<int, int> leftMaxMin = dfs_naive(root->left, maxDiff);
        std::pair<int, int> rightMaxMin = dfs_naive(root->right, maxDiff);

        int maxDecendant = std::max(leftMaxMin.first, rightMaxMin.first);
        int minDecendant = std::min(leftMaxMin.second, rightMaxMin.second);

        maxDiff = std::max(maxDiff, 
                        std::max(std::abs(maxDecendant - root->val), std::abs(minDecendant - root->val)));  
        
        return {std::max(maxDecendant, root->val), std::min(minDecendant, root->val)};
    }
public:
    int maxAncestorDiff(TreeNode* root) {
        //int maxDiff = 0;
        //dfs_naive(root, maxDiff);

        //return maxDiff;

        return dfs_better(root, root->val, root->val);
    }
};