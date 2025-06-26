/*
Given the root of a binary tree, return the sum of all left leaves.

A leaf is a node with no children. A left leaf is a leaf that is the left child of another node.

 

Example 1:

Input: root = [3,9,20,null,null,15,7]
Output: 24
Explanation: There are two left leaves in the binary tree, with values 9 and 15 respectively.

Example 2:

Input: root = [1]
Output: 0

 

Constraints:

    The number of nodes in the tree is in the range [1, 1000].
    -1000 <= Node.val <= 1000



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
    void dfs(TreeNode* root, bool is_left, int& sum) {
        if (root == nullptr) {
            return;
        }

        if (root->left == nullptr && root->right == nullptr && is_left) {
            sum += root->val;
            return;
        }

        dfs(root->left, true, sum);
        dfs(root->right, false, sum);
    }
    int by_dfs(TreeNode* root) {
        int sum = 0;
        dfs(root, false, sum);
        return sum;
    }
public:
    int sumOfLeftLeaves(TreeNode* root) {
        return by_dfs(root);
    }
};

/*
class Solution {
private:
    bool isLeaf(TreeNode* now) {
        if (now->right == NULL && now->left == NULL) {
            return true;
        }

        return false;
    }
    
    void preorder(TreeNode* now, int& sum) {
        std::stack<TreeNode*> s;
        s.push(now);

        TreeNode* curr = NULL;
        TreeNode* leftChild = NULL;
        while (!s.empty()) {
            curr = s.top();
            s.pop();
            
            //put into stack from right to left
            if (curr->right != NULL) {
                s.push(curr->right);
            }
            
            if (curr->left != NULL) {
                s.push(curr->left);

                leftChild = curr->left;
                if (isLeaf(leftChild)) {
                    sum += leftChild->val;
                }
            }
        }

    }
public:
    int sumOfLeftLeaves(TreeNode* root) {
        int sum = 0;
        preorder(root, sum);

        return sum;
    }
};
*/