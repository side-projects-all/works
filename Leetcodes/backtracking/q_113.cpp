/*
Given the root of a binary tree and an integer targetSum, return all root-to-leaf paths where the sum of the node values in the path equals targetSum. Each path should be returned as a list of the node values, not node references.

A root-to-leaf path is a path starting from the root and ending at any leaf node. A leaf is a node with no children.

 

Example 1:

Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
Output: [[5,4,11,2],[5,8,4,5]]
Explanation: There are two paths whose sum equals targetSum:
5 + 4 + 11 + 2 = 22
5 + 8 + 4 + 5 = 22

Example 2:

Input: root = [1,2,3], targetSum = 5
Output: []

Example 3:

Input: root = [1,2], targetSum = 0
Output: []

 

Constraints:

    The number of nodes in the tree is in the range [0, 5000].
    -1000 <= Node.val <= 1000
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
    std::vector<std::vector<int>> dfs(TreeNode* root, int targetSum) {
        std::vector<std::vector<int>> ans;
        if (root == nullptr) {
            return ans;
        }

        std::vector<int> curr;

        std::function<void(TreeNode*, int)> re = [&](TreeNode* now, int currSum) {
            //base case: reach leaf
            if (now->left == nullptr && now->right == nullptr) {
                if (currSum + now->val == targetSum) {
                    curr.push_back(now->val);
                    ans.push_back(curr);
                    curr.pop_back();
                }

                return;
            }

            if (now != nullptr) {
                curr.push_back(now->val);

                if (now->left != nullptr) {
                    re(now->left, currSum + now->val);
                }
                
                if (now->right != nullptr) {
                    re(now->right, currSum + now->val);
                }
                curr.pop_back();
            }
        };

        re(root, 0);

        return ans;
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        return dfs(root, targetSum);
    }
};