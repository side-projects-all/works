/*
Given the root of a binary tree, flatten the tree into a "linked list":

    The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
    The "linked list" should be in the same order as a pre-order traversal of the binary tree.

 

Example 1:

Input: root = [1,2,5,3,4,null,6]
Output: [1,null,2,null,3,null,4,null,5,null,6]

Example 2:

Input: root = []
Output: []

Example 3:

Input: root = [0]
Output: [0]

 

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
    TreeNode* recursive(TreeNode* now) {
        if (now == nullptr) {
            return nullptr;
        }

        if (now->left == nullptr && now->right == nullptr) {
            return now;
        }

        TreeNode* left_last = recursive(now->left);
        TreeNode* right_last = recursive(now->right);

        if (left_last != nullptr) {
            left_last->right = now->right;
            now->right = now->left;
            now->left = nullptr;
        }

        return right_last == nullptr ? left_last : right_last;
    }
    void naive(TreeNode* now) {
        std::vector<TreeNode*> v;
        std::function<void(TreeNode*)> preorder = [&](TreeNode* now) {
            if (now == nullptr) {
                return;
            }

            v.push_back(now);

            preorder(now->left);
            preorder(now->right);
        };

        preorder(now);

        for (int i = 0; i < v.size() - 1; ++i) {
            v[i]->right = v[i + 1];
            v[i]->left = nullptr;
        }
    }
    
public:
    void flatten(TreeNode* root) {
        if (root == nullptr || (root->left == nullptr && root->right == nullptr)) {
            return;
        }

        //naive(root);
        recursive(root);
    }
};