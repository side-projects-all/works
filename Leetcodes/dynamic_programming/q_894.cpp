/*
Given an integer n, return a list of all possible full binary trees with n nodes. Each node of each tree in the answer must have Node.val == 0.

Each element of the answer is the root node of one possible tree. You may return the final list of trees in any order.

A full binary tree is a binary tree where each node has exactly 0 or 2 children.

 

Example 1:

Input: n = 7
Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]

Example 2:

Input: n = 3
Output: [[0,0,0]]

 

Constraints:

    1 <= n <= 20


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
    
    std::vector<TreeNode*> iterative(int n) {
        if (n % 2 == 0) {
            return {};
        }

        std::vector<std::vector<TreeNode*>> mem(n + 1);
        
        mem[1].push_back({ new TreeNode() });
        for (int cnt = 3; cnt <= n; cnt += 2) {
            for (int i = 1; i < cnt - 1; i += 2) {
                int j = cnt - 1 - i;

                for (auto nodeL : mem[i]) {
                    for (auto nodeR : mem[j]) {
                        TreeNode* root = new TreeNode(0, nodeL, nodeR);
                        mem[cnt].push_back(root);
                    }
                }
            }
        }

        return mem[n];
    }
    std::vector<TreeNode*> recursive(int n) {
        std::vector<std::vector<TreeNode*>> mem(n + 1);

        std::function<std::vector<TreeNode*>(int)> recurr = [&](int n_now) -> std::vector<TreeNode*> {
            if (n_now % 2 == 0) {
                return {};
            }

            if (n_now == 1) {
                return { new TreeNode() };
            }

            if (!mem[n_now].empty()) {
                return mem[n_now];
            }

            std::vector<TreeNode*> ans;
            for (int i = 1; i < n_now; i += 2) {
                std::vector<TreeNode*> left = recurr(i);
                std::vector<TreeNode*> right = recurr(n_now - i - 1);

                for (auto& nodeL : left) {
                    for (auto& nodeR : right) {
                        TreeNode* root = new TreeNode(0, nodeL, nodeR);
                        ans.push_back(root);
                    }
                }
            }

            return mem[n] = ans;
        };

        return recurr(n);
    }
public:
    vector<TreeNode*> allPossibleFBT(int n) {
        //return recursive(n);
        return iterative(n);
    }
};