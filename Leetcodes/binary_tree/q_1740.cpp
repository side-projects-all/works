/*
Given the root of a binary tree and two integers p and q, return the distance between the nodes of value p and value q in the tree.

The distance between two nodes is the number of edges on the path from one to the other.

 

Example 1:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 0
Output: 3
Explanation: There are 3 edges between 5 and 0: 5-3-1-0.

Example 2:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 7
Output: 2
Explanation: There are 2 edges between 5 and 7: 5-2-7.

Example 3:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 5
Output: 0
Explanation: The distance between a node and itself is 0.

 

Constraints:

    The number of nodes in the tree is in the range [1, 10^4].
    0 <= Node.val <= 10^9
    All Node.val are unique.
    p and q are values in the tree.


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
    int dfs(TreeNode* now, int p, int q, int curr_depth) {
        if (now == nullptr || p == q) {
            return 0;
        }

        if (now->val == p || now->val == q) {
            //this part can handle the case: two nodes are on the same sub tree, 
            //and one is a sub node of the other one
            int left = dfs(now->left, p, q, 1);
            int right = dfs(now->right, p, q, 1);

            return (left > 0 || right > 0) ? std::max(left, right) : curr_depth;
        }

        int left = dfs(now->left, p, q, curr_depth + 1);
        int right = dfs(now->right, p, q, curr_depth + 1);
        int dis = left + right;

        if (left != 0 && right != 0) {
            dis -= 2 * curr_depth;
        }

        return dis;
    }
public:
    int findDistance(TreeNode* root, int p, int q) {

        return dfs(root, p, q, 0);
    }
};