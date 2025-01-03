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
    int iterative(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        //turn the node-based tree into array-based tree with BFS traverse
        std::vector<int> tree;

        //use map to show parent-children relationship
        std::unordered_map<int, std::vector<int>> graph;

        int index = -1;
        std::queue<TreeNode*> q_node;
        q_node.push(root);
        std::queue<int> q_index;
        q_index.push(index);

        while(!q_node.empty()) {
            TreeNode* node = q_node.front();
            q_node.pop();
            int parent_index = q_index.front();
            q_index.pop();

            if (node != nullptr) {
                ++index;
                tree.push_back(node->val);
                graph[parent_index].push_back(index);

                q_node.push(node->left);
                q_index.push(index);
                q_node.push(node->right);
                q_index.push(index);
            }
        }

        std::vector<int> rob(index + 1);
        std::vector<int> not_rob(index + 1);

        for (int i = index; i > -1; --i) {
            std::vector<int> children = graph[i];

            if (children.empty()) {
                rob[i] = tree[i];
                not_rob[i] = 0;
            } else {
                rob[i] = tree[i];

                for (int child : children) {
                    rob[i] += not_rob[child];
                    not_rob[i] += std::max(rob[child], not_rob[child]);
                }
            }
        }

        return std::max(rob[0], not_rob[0]);
    }

    int recursive_with_mem(TreeNode* root, bool prev_robbed, 
                                            std::unordered_map<TreeNode*, int>& robbed, 
                                                std::unordered_map<TreeNode*, int>& notRobbed) {

        if (root == nullptr) {
            return 0;
        }

        int result = 0;
        if (prev_robbed) {
            if (robbed.find(root) != robbed.end()) {
                return robbed[root];
            }

            result = recursive_with_mem(root->left, false, robbed, notRobbed) + 
                        recursive_with_mem(root->right, false, robbed, notRobbed);

            robbed[root] = result;

        } else {
            if (notRobbed.find(root) != notRobbed.end()) {
                return notRobbed[root];
            }

            int robNow = root->val + recursive_with_mem(root->left, true, robbed, notRobbed) + 
                        recursive_with_mem(root->right, true, robbed, notRobbed);

            int notRobNow = recursive_with_mem(root->left, false, robbed, notRobbed) + 
                                recursive_with_mem(root->right, false, robbed, notRobbed);

            result = std::max(robNow, notRobNow);

            notRobbed[root] = result;
        }

        return result;
    }

    std::vector<int> recursive(TreeNode* root) {
        if (root == nullptr) {
            return {0, 0};
        }

        std::vector<int> left = recursive(root->left);
        std::vector<int> right = recursive(root->right);

        int rob = root->val + left[1] + right[1];
        int notRob = std::max(left[0], left[1]) + std::max(right[0], right[1]);

        return {rob, notRob};
    }
public:
    int rob(TreeNode* root) {
        //std::vector<int> ans = recursive(root);
        //return std::max(ans[0], ans[1]);

        //std::unordered_map<TreeNode*, int> robbed;
        //std::unordered_map<TreeNode*, int> notRobbed;

        //return recursive_with_mem(root, false, robbed, notRobbed);

        return iterative(root);
    }
};