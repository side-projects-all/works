/*
Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

 

Example 1:

Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
Output: 6
Explanation: The LCA of nodes 2 and 8 is 6.

Example 2:

Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
Output: 2
Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.

Example 3:

Input: root = [2,1], p = 2, q = 1
Output: 2

 

Constraints:

    The number of nodes in the tree is in the range [2, 10^5].
    -10^9 <= Node.val <= 10^9
    All Node.val are unique.
    p != q
    p and q will exist in the BST.


*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
private:
    TreeNode* recursive(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) {
            return nullptr;
        }

        if (root->val > p->val && root->val > q->val) {
            return recursive(root->left, p, q);

        } else if (root->val < p->val && root->val < q->val) {
            return recursive(root->right, p, q);
        }
        
        return root;
    }
    TreeNode* iterative(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* now = root;

        while (now != nullptr) {

            if (now->val > p->val && now->val > q->val) {
                now = now->left;

            } else if (now->val < p->val && now->val < q->val) {
                now = now->right;
                
            } else {
                break;
            }
        }

        return now;
    }

    int recursive_236(TreeNode* curr, TreeNode* p, TreeNode* q, TreeNode*& ans) {
        if (curr == nullptr) {
            return 0;
        }

        int left = recursive_235(curr->left, p, q, ans);
        int right = recursive_235(curr->right, p, q, ans);
        int now = (curr == p || curr == q) ? 1 : 0;

        if (left + right + now >= 2) {
            ans = curr;
        }

        return left + right + now > 0;
    }

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //return recursive(root, p, q);
        return iterative(root, p, q);
        //TreeNode* ans = nullptr;
        //recursive_236(root, p, q, ans);

        //return ans;
    }
};