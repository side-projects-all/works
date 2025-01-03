/*
Given the root of a binary tree, return the average value of the nodes on each level in the form of an array. Answers within 10-5 of the actual answer will be accepted.

 

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: [3.00000,14.50000,11.00000]
Explanation: The average value of nodes on level 0 is 3, on level 1 is 14.5, and on level 2 is 11.
Hence return [3, 14.5, 11].

Example 2:

Input: root = [3,9,20,15,7]
Output: [3.00000,14.50000,11.00000]

 

Constraints:

    The number of nodes in the tree is in the range [1, 10^4].
    -2^31 <= Node.val <= 2^31 - 1

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
    vector<double> bfs(TreeNode* root) {
        std::vector<double> result;
        
        std::queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int len = q.size();

            //use the len to differentiate the level
            double sum = 0.0;
            for (int i = 0; i < len; ++i) {
                TreeNode* n = q.front();
                q.pop();

                sum += n->val;
                
                if (n->left != nullptr) {
                    q.push(n->left);
                }

                if (n->right != nullptr) {
                    q.push(n->right);
                }
            }

            sum = sum / len;

            result.push_back(sum);
        }

        return result;
    }
public:
    vector<double> averageOfLevels(TreeNode* root) {
        return bfs(root);
    }
};