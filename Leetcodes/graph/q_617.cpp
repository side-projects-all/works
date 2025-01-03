/*
You are given two binary trees root1 and root2.

Imagine that when you put one of them to cover the other, some nodes of the two trees are overlapped while the others are not. You need to merge the two trees into a new binary tree. The merge rule is that if two nodes overlap, then sum node values up as the new value of the merged node. Otherwise, the NOT null node will be used as the node of the new tree.

Return the merged tree.

Note: The merging process must start from the root nodes of both trees.

 

Example 1:

Input: root1 = [1,3,2,5], root2 = [2,1,3,null,4,null,7]
Output: [3,4,5,5,4,null,7]

Example 2:

Input: root1 = [1], root2 = [1,2]
Output: [2,2]

 

Constraints:

    The number of nodes in both trees is in the range [0, 2000].
    -104 <= Node.val <= 10^4


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
    TreeNode* dfs_iterative(TreeNode* root1, TreeNode* root2) {
        //corner case
        if (root1 == nullptr) {
            return root2;
        }

        std::stack<std::pair<TreeNode*, TreeNode*>> s;
        s.push({root1, root2});

        while (!s.empty()) {

            std::pair<TreeNode*, TreeNode*> p = s.top();
            s.pop();
            TreeNode* r1 = p.first;
            TreeNode* r2 = p.second;

            if (r1 == nullptr || r2 == nullptr) {
                continue;
            }
            
            r1->val += r2->val;

            if (r1->left == nullptr) {
                r1->left = r2->left;
            } else {
                s.push({r1->left, r2->left});
            }

            if (r1->right == nullptr) {
                r1->right = r2->right;
            } else {
                s.push({r1->right, r2->right});
            }
        }

        return root1;
    }
    TreeNode* dfs_recursive(TreeNode*& root1, TreeNode* root2) {

        if (root2 == nullptr) {
            return root1;
        }

        if (root1 == nullptr) {
            return root2;
        }

        root1->val += root2->val;

        root1->left = dfs_recursive(root1->left, root2->left);
        root1->right = dfs_recursive(root1->right, root2->right);

        return root1;
    }
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        
        //return dfs_recursive(root1, root2);

        return dfs_iterative(root1, root2);
    }
};