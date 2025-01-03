/*
Given the root of a binary tree and two integers val and depth, add a row of nodes with value val at the given depth depth.

Note that the root node is at depth 1.

The adding rule is:

    Given the integer depth, for each not null tree node cur at the depth depth - 1, create two tree nodes with value val as cur's left subtree root and right subtree root.
    cur's original left subtree should be the left subtree of the new left subtree root.
    cur's original right subtree should be the right subtree of the new right subtree root.
    If depth == 1 that means there is no depth depth - 1 at all, then create a tree node with value val as the new root of the whole original tree, and the original tree is the new root's left subtree.

 

Example 1:

Input: root = [4,2,6,3,1,5], val = 1, depth = 2
Output: [4,1,1,2,null,null,6,3,1,5]

Example 2:

Input: root = [4,2,null,3,1], val = 1, depth = 3
Output: [4,2,null,1,1,3,null,null,1]

 

Constraints:

    The number of nodes in the tree is in the range [1, 10^4].
    The depth of the tree is in the range [1, 10^4].
    -100 <= Node.val <= 100
    -10^5 <= val <= 10^5
    1 <= depth <= the depth of tree + 1


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
    TreeNode* iterative(TreeNode* root, int val, int depth) {
        std::stack<std::pair<TreeNode*, int>> s;
        s.push({root, 1});

        while (!s.empty()) {
            auto [now, depth_now] = s.top();
            s.pop();

            if (now == nullptr) {
                continue;
            }

            if (depth_now == depth - 1) {
                TreeNode* tmp_left = now->left;
                TreeNode* new_left = new TreeNode(val, tmp_left, nullptr);
                now->left = new_left;

                TreeNode* tmp_right = now->right;
                TreeNode* new_right = new TreeNode(val, nullptr, tmp_right);
                now->right = new_right;
                
            } else {
                s.push({now->right, depth_now + 1});
                s.push({now->left, depth_now + 1});
            }

        }

        return root;
    }
    TreeNode* recursive(TreeNode* root, int val, int depth) {
        
        std::function<void(int, TreeNode*)> re = [&](int depth_now, TreeNode* now) {
            if (now == nullptr) {
                return;
            }

            if (depth_now == depth - 1) {
                TreeNode* tmp_left = now->left;
                TreeNode* new_left = new TreeNode(val, tmp_left, nullptr);
                now->left = new_left;

                TreeNode* tmp_right = now->right;
                TreeNode* new_right = new TreeNode(val, nullptr, tmp_right);
                now->right = new_right;
                return;
            }

            re(depth_now + 1, now->left);
            re(depth_now + 1, now->right);
        };

        re(1, root);

        return root;
    }
public:
    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        //corner case
        if (depth == 1) {
            TreeNode* new_root = new TreeNode(val, root, nullptr);
            return new_root;
        }

        return recursive(root, val, depth);
        //return iterative(root, val, depth);
    }
};