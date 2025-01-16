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

    struct pair_hash {
    private:
        // A better hash combining function (inspired by Boost's hash_combine)
        template <class T>
        inline void hash_combine(std::size_t& seed, const T& v) const {
            std::hash<T> hasher;
            seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
    public:
        template <class T1, class T2>
        std::size_t operator() (const std::pair<T1, T2>& p) const {
            std::size_t seed = 0;
            hash_combine(seed, p.first);
            hash_combine(seed, p.second);
            return seed;
        }
    };
    vector<TreeNode*> recursive(int b, int e, std::unordered_map<std::pair<int, int>, std::vector<TreeNode*>, pair_hash>& mem) {

        std::vector<TreeNode*> combination;
        if (b > e) {
            combination.push_back(nullptr);
            return combination;
        }

        if (mem.find({b, e}) != mem.end()) {
            return mem[{b, e}];
        }

        for (int i = b; i <= e; ++i) {
            std::vector<TreeNode*> l_sub = recursive(b, i - 1, mem);
            std::vector<TreeNode*> r_sub = recursive(i + 1, e, mem);

            for (TreeNode* l : l_sub) {
                for (TreeNode* r : r_sub) {
                    TreeNode* root = new TreeNode(i, l, r);
                    combination.push_back(root);
                }
            }
        }

        return mem[{b, e}] = combination;
    }
    vector<TreeNode*> by_recursive_dp(int& n) {
        std::unordered_map<std::pair<int, int>, std::vector<TreeNode*>, pair_hash> mem;

        return recursive(1, n, mem);
    }
public:
    vector<TreeNode*> generateTrees(int n) {

        //return iterative(n);
        return by_recursive_dp(n);
    }
};