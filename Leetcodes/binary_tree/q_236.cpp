/*
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

 

Example 1:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.

Example 2:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.

Example 3:

Input: root = [1,2], p = 1, q = 2
Output: 1

 

Constraints:

    The number of nodes in the tree is in the range [2, 10^5].
    -10^9 <= Node.val <= 10^9
    All Node.val are unique.
    p != q
    p and q will exist in the tree.


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
    bool dfs(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode*& ans) {
        if (root == nullptr) {
            return false;
        }

        int left = dfs(root->left, p, q, ans);
        int right = dfs(root->right, p, q, ans);
        int curr = (root == p || root == q);

        if (curr + left + right >= 2) {
            ans = root;
        }

        return curr + left + right >= 1;
    }
    
    TreeNode* iterative(TreeNode* root, TreeNode* p, TreeNode* q) {
        std::stack<TreeNode*> stack;
        std::unordered_map<TreeNode*, TreeNode*> parent;    //key: the node now, val: its parent

        parent[root] = nullptr;
        stack.push(root);

        while (!parent.count(p) || !parent.count(q)) {
            TreeNode* n = stack.top();
            stack.pop();

            if (n->left != nullptr) {
                parent[n->left] = n;
                stack.push(n->left);
            }

            if (n->right != nullptr) {
                parent[n->right] = n;
                stack.push(n->right);
            }
        }

        std::unordered_set<TreeNode*> ancestors;
        while (p != nullptr) {
            ancestors.insert(p);
            p = parent[p];
        }

        while (!ancestors.count(q)) {
            q = parent[q];
        }

        return q;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        TreeNode* ans = nullptr;
        dfs(root, p, q, ans);
        return ans;
        //return iterative(root, p, q);
    }
};