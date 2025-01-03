/*
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
public:
    bool isValidBST(TreeNode* root) {

        //return recursive(root, nullptr, nullptr);
        return inorder_recursive(root);
    }
private:
    //those ways below are so genius!
    bool recursive(TreeNode* root, TreeNode* low, TreeNode* high) {
        if (root == nullptr) {
            return true;
        }

        if ((low != nullptr && root->val <= low->val) || (high != nullptr && root->val >= high->val)) {
            return false;
        }

        return recursive(root->left, low, root) && recursive(root->right, root, high);
    }


    bool inorder_recursive(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        
        if (!inorder_recursive(root->left)) {
            return false;
        }

        //this is for the root inside the recursive function to check!!
        //except for the most beginning left-most sub-node,
        //right sub-node belong to left sub-part and nodes belong to right sub-part 
        //could all be applied to this rule!!
        //unbelievable
        if (prev != nullptr && root->val <= prev->val) {
            return false;
        }

        prev = root;
        return inorder_recursive(root->right);
    }

    TreeNode* prev = nullptr;
};