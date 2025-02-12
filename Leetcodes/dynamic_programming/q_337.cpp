/*
The thief has found himself a new place for his thievery again. There is only one entrance to this area, called root.

Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that all houses in this place form a binary tree. It will automatically contact the police if two directly-linked houses were broken into on the same night.

Given the root of the binary tree, return the maximum amount of money the thief can rob without alerting the police.

 

Example 1:

Input: root = [3,2,3,null,3,null,1]
Output: 7
Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.

Example 2:

Input: root = [3,4,5,1,3,null,1]
Output: 9
Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.

 

Constraints:

    The number of nodes in the tree is in the range [1, 10^4].
    0 <= Node.val <= 10^4


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
    int recursive(TreeNode* root, bool pre_robbed, std::unordered_map<TreeNode*, int>& robbed, std::unordered_map<TreeNode*, int>& not_robbed) {
        if (root == nullptr) {
            return 0;
        }

        if (pre_robbed) {
            if (not_robbed.find(root) != not_robbed.end()) {
                return robbed[root];
            }

            return not_robbed[root] = recursive(root->left, !pre_robbed, robbed, not_robbed) + recursive(root->right, !pre_robbed, robbed, not_robbed);

        } 

        if (robbed.find(root) != robbed.end()) {
            return robbed[root];
        }

        int curr_rob = root->val + recursive(root->left, !pre_robbed, robbed, not_robbed) + recursive(root->right, !pre_robbed, robbed, not_robbed);
        int curr_not_rob = recursive(root->left, pre_robbed, robbed, not_robbed) + recursive(root->right, pre_robbed, robbed, not_robbed);

        return robbed[root] = std::max(curr_rob, curr_not_rob);
    }
    int by_recursive_dp(TreeNode* root) {
        std::unordered_map<TreeNode*, int> robbed;
        std::unordered_map<TreeNode*, int> not_robbed;
        return recursive(root,false, robbed, not_robbed);
    }

    std::pair<int, int> recursive2(TreeNode* root) {
        if (root == nullptr) {
            return {0, 0};
        }

        std::pair<int, int> left_sub = recursive2(root->left);
        std::pair<int, int> right_sub = recursive2(root->right);

        //rob now, then we need left right sub without rob
        int rob = root->val + left_sub.second + right_sub.second;   
        int not_rob = std::max(left_sub.first, left_sub.second) + std::max(right_sub.first, right_sub.second);

        return {rob, not_rob};
    }
    int by_recursive2(TreeNode* root) {
        std::pair<int, int> p = recursive2(root);   //first: rob, second: not rob

        return std::max(p.first, p.second);
    }
public:
    int rob(TreeNode* root) {
        //return by_recursive_dp(root);

        return by_recursive2(root);
    }
};