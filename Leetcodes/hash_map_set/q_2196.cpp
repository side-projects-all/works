/*
You are given a 2D integer array descriptions where descriptions[i] = [parenti, childi, isLefti] indicates that parenti is the parent of childi in a binary tree of unique values. Furthermore,

    If isLefti == 1, then childi is the left child of parenti.
    If isLefti == 0, then childi is the right child of parenti.

Construct the binary tree described by descriptions and return its root.

The test cases will be generated such that the binary tree is valid.

 

Example 1:

Input: descriptions = [[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]]
Output: [50,20,80,15,17,19]
Explanation: The root node is the node with value 50 since it has no parent.
The resulting binary tree is shown in the diagram.

Example 2:

Input: descriptions = [[1,2,1],[2,3,0],[3,4,1]]
Output: [1,2,null,null,3,4]
Explanation: The root node is the node with value 1 since it has no parent.
The resulting binary tree is shown in the diagram.

 

Constraints:

    1 <= descriptions.length <= 10^4
    descriptions[i].length == 3
    1 <= parenti, childi <= 10^5
    0 <= isLefti <= 1
    The binary tree described by descriptions is valid.


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
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        std::unordered_map<int, TreeNode*> adj;
        std::unordered_set<int> children;

        for (const auto& v : descriptions) {
            int p = v[0];
            int c = v[1];
            bool is_left = v[2];

            if (adj.find(p) == adj.end()) {
                adj[p] = new TreeNode(p);
            }

            if (adj.find(c) == adj.end()) {
                adj[c] = new TreeNode(c);
            }

            if (is_left) {
                adj[p]->left = adj[c];
            } else {
                adj[p]->right = adj[c];
            }

            children.insert(c);
        }

        for (auto& p : adj) {
            
            if (children.find(p.first) == children.end()) {
                return p.second;
            }
        }

        return nullptr;
    }
};