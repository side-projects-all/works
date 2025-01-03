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
private:
    TreeNode* clone(TreeNode* node, int offset) {
        if (node == nullptr) {
            return nullptr;
        }

        TreeNode* cloneNode = new TreeNode(node->val + offset);
        cloneNode->left = clone(node->left, offset);
        cloneNode->right = clone(node->right, offset);

        return cloneNode;
    }
    std::vector<TreeNode*> iterative_space_optimize(int n) {
        std::vector<std::vector<TreeNode*>> mem(n + 1);
        mem[0].push_back(nullptr);

        for (int numOfNodes = 1; numOfNodes <= n; ++numOfNodes) {
            for (int i = 1; i <= numOfNodes; ++i) {
                int j = numOfNodes - i;

                for (TreeNode* left : mem[i - 1]) {
                    for (TreeNode* right : mem[j]) {
                        TreeNode* root = new TreeNode(i, left, clone(right, i));
                        mem[numOfNodes].push_back(root);
                    }
                }
            }
        }

        return mem[n];
    }
    std::vector<TreeNode*> iterative(int n) {
        std::vector<std::vector<std::vector<TreeNode*>>> mem(n + 1, 
                                                            std::vector(n + 1, 
                                                                std::vector<TreeNode*>(0)));

        for (int i = 1; i <= n; ++i) {
            mem[i][i].push_back(new TreeNode(i));
        }

        for (int numOfNodes = 2; numOfNodes <= n; ++numOfNodes) {
            for (int start = 1; start <= n - numOfNodes + 1; ++start) {
                int end = start + numOfNodes - 1;

                for (int i = start; i <= end; ++i) {
                    std::vector<TreeNode*> leftSubs = (i - 1 >= start) ? mem[start][i - 1] : 
                                                                            std::vector<TreeNode*>({nullptr});
                    std::vector<TreeNode*> rightSubs = (i + 1 <= end) ? mem[i + 1][end] : 
                                                                            std::vector<TreeNode*>({nullptr});

                    for (TreeNode* left : leftSubs) {
                        for (TreeNode* right : rightSubs) {
                            TreeNode* root = new TreeNode(i, left, right);
                            mem[start][end].push_back(root);
                        }
                    }
                }
            }
        }

        return mem[1][n];
    }

    struct KeyHash {
        template<class t1, class t2>
        std::size_t operator()(const std::pair<t1, t2>& k) const {
            return std::hash<t1>()(k.first) ^ (std::hash<t2>()(k.second) << 1);
        }
    };
    
    struct KeyEqual {
        template<class t1, class t2>
        bool operator()(const std::pair<t1, t2>& key1, const std::pair<t1, t2>& key2) const {
            return key1.first == key2.first && key1.second == key2.second;
        }
    };

    std::vector<TreeNode*> recurisve(int start, int end, std::unordered_map<std::pair<int, int>, 
                                                        std::vector<TreeNode*>, KeyHash, KeyEqual> mem) {

        std::vector<TreeNode*> result;

        if (start > end) {
            result.push_back(nullptr);
            return result;
        }

        std::pair<int, int> p = std::make_pair(start, end);
        if (mem.find(p) != mem.end()) {
            return mem[p];
        }

        for (int i = start; i <= end; ++i) {
            std::vector<TreeNode*> leftSubs = recurisve(start, i - 1, mem);
            std::vector<TreeNode*> rightSubs = recurisve(i + 1, end, mem);

            for (TreeNode* left : leftSubs) {
                for (TreeNode* right : rightSubs) {
                    TreeNode* root = new TreeNode(i, left, right);
                    result.push_back(root);
                }
            }
        }

        return result;
    }
public:
    vector<TreeNode*> generateTrees(int n) {

        //std::unordered_map<std::pair<int, int>, std::vector<TreeNode*>, KeyHash, KeyEqual> mem;

        //return recurisve(1, n, mem);
        return iterative(n);
        //return iterative_space_optimize(n);
    }
};