/*
Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).

 

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: [[3],[20,9],[15,7]]

Example 2:

Input: root = [1]
Output: [[1]]

Example 3:

Input: root = []
Output: []

 

Constraints:

    The number of nodes in the tree is in the range [0, 2000].
    -100 <= Node.val <= 100


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
    vector<vector<int>> by_bfs(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }

        std::vector<std::vector<int>> ans;
        bool left_to_right = true;
        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {

            std::vector<int> tmp;
            int len = q.size();
            for (int i = 0; i < len; ++i) {
                tmp.push_back(q.front()->val);

                if (q.front()->left != nullptr) {
                    q.push(q.front()->left);
                }
                if (q.front()->right != nullptr) {
                    q.push(q.front()->right);
                }
            
                q.pop();
            }

            if (!left_to_right) {
                std::reverse(tmp.begin(), tmp.end());
            }
            
            left_to_right = !left_to_right;
            ans.push_back(tmp);
        }

        return ans;
    }
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        return by_bfs(root);
    }
};