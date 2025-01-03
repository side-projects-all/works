/*
Given an integer n, return all the structurally unique BST's (binary search trees), which has exactly n nodes of unique values from 1 to n. Return the answer in any order.

 

Example 1:

Input: n = 3
Output: [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]

Example 2:

Input: n = 1
Output: [[1]]

 

Constraints:

    1 <= n <= 8


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
    vector<TreeNode*> generateTrees(int n) {
         
        return allPossibleBST(1, n);
    }

private:
    //need to use map? why?
    std::map<std::pair<int, int>, std::vector<TreeNode*>> mem;

    std::vector<TreeNode*> allPossibleBST(int start, int end) {
        std::vector<TreeNode*> result;

        if (start > end) {
            result.push_back(nullptr);
            return result;
        }

        std::pair<int, int> key = std::make_pair(start, end);
        if (mem.find(key) != mem.end()) {
            return mem[key];
        }

        for (int i = start; i <= end; ++i) {
            std::vector<TreeNode*> leftSubtrees = allPossibleBST(start, i - 1);
            std::vector<TreeNode*> rightSubtrees = allPossibleBST(i + 1, end);

            for (TreeNode* left: leftSubtrees) {
                for (TreeNode* right: rightSubtrees) {
                    TreeNode* root = new TreeNode(i);
                    root->left = left;
                    root->right = right;
                    result.push_back(root);
                }
            }

        }

        mem[std::make_pair(start, end)] = result;
        
        return mem[std::make_pair(start, end)];
    }
};