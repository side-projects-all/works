/*
You are given the root of a binary tree with n nodes. Each node is uniquely assigned a value from 1 to n. You are also given an integer startValue representing the value of the start node s, and a different integer destValue representing the value of the destination node t.

Find the shortest path starting from node s and ending at node t. Generate step-by-step directions of such path as a string consisting of only the uppercase letters 'L', 'R', and 'U'. Each letter indicates a specific direction:

    'L' means to go from a node to its left child node.
    'R' means to go from a node to its right child node.
    'U' means to go from a node to its parent node.

Return the step-by-step directions of the shortest path from node s to node t.

 

Example 1:

Input: root = [5,1,2,3,null,6,4], startValue = 3, destValue = 6
Output: "UURL"
Explanation: The shortest path is: 3 → 1 → 5 → 2 → 6.

Example 2:

Input: root = [2,1], startValue = 2, destValue = 1
Output: "L"
Explanation: The shortest path is: 2 → 1.

 

Constraints:

    The number of nodes in the tree is n.
    2 <= n <= 10^5
    1 <= Node.val <= n
    All the values in the tree are unique.
    1 <= startValue, destValue <= n
    startValue != destValue


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
    TreeNode* lowest_common_ancestor(TreeNode* now, int& s, int& d) {
        if (now == nullptr) {
            return nullptr;
        }

        if (now->val == s || now->val == d) {
            return now;
        }

        TreeNode* left = lowest_common_ancestor(now->left, s, d);
        TreeNode* right = lowest_common_ancestor(now->right, s, d);

        if (left == nullptr) {
            return right;
        } else if (right == nullptr) {
            return left;
        } else {
            return now;
        }
    }

    bool find_path(TreeNode* now, int val, std::string& path) {
        if (now == nullptr) {
            return false;
        }

        if (now->val == val) {
            return true;
        }

        path.push_back('L');
        if (find_path(now->left, val, path)) {
            return true;
        }

        path.pop_back();

        path.push_back('R');
        if (find_path(now->right, val, path)) {
            return true;
        }

        path.pop_back();

        return false;
    }
public:
    string getDirections(TreeNode* root, int startValue, int destValue) {
        TreeNode* lca = lowest_common_ancestor(root, startValue, destValue);

        std::string path_to_s;
        std::string path_to_d;

        find_path(lca, startValue, path_to_s);
        find_path(lca, destValue, path_to_d);

        std::string dir(path_to_s.size(), 'U');
        dir.append(path_to_d);
        return dir;
    }
};