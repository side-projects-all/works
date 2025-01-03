/*
Given the root of a binary tree, the value of a target node target, and an integer k, return an array of the values of all nodes that have a distance k from the target node.

You can return the answer in any order.

 

Example 1:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
Output: [7,4,1]
Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1.

Example 2:

Input: root = [1], target = 1, k = 3
Output: []

 

Constraints:

    The number of nodes in the tree is in the range [1, 500].
    0 <= Node.val <= 500
    All the values Node.val are unique.
    target is the value of one of the nodes in the tree.
    0 <= k <= 1000


*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    void buildAdj(TreeNode* root, std::unordered_map<int, std::vector<int>>& adj) {
        std::queue<TreeNode*> q;

        q.push(root);

        while (!q.empty()) {

            TreeNode* n = q.front();
            q.pop();

            if (n->left != nullptr) {
                q.push(n->left);
                adj[n->val].push_back(n->left->val);
                adj[n->left->val].push_back(n->val);
            }

            if (n->right != nullptr) {
                q.push(n->right);
                adj[n->val].push_back(n->right->val);
                adj[n->right->val].push_back(n->val);
            }
        }
    }

    std::vector<int> bfs(TreeNode* target, int k, std::unordered_map<int, std::vector<int>>& adj) {
        std::vector<int> result;

        //do bfs again, start from target node to find all nodes that have distance k.
        int val = target->val;

        std::queue<int> q;
        std::unordered_set<int> visited;
        q.push(val);

        int distance = 0;

        while (!q.empty()) {

            int qLen = q.size();

            for (int i = 0; i < qLen; ++i) {
                int node = q.front();
                q.pop();

                if (visited.find(node) == visited.end()) {
                    visited.insert(node);

                    for (int n : adj[node]) {
                        if (visited.find(n) == visited.end()) {
                            q.push(n);
                        }
                        
                    }
                }
            }
            
            ++distance;

            if (distance == k) {
                while (!q.empty()) {
                    result.push_back(q.front());
                    q.pop();
                }
            }
        }

        return result;
    }
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        //corner case
        if (k == 0) {
            return {target->val};
        }

        std::unordered_map<int, std::vector<int>> adj;
        buildAdj(root, adj);

        return bfs(target, k, adj);
    }
};