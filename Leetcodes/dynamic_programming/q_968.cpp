/*
You are given the root of a binary tree. We install cameras on the tree nodes where each camera at a node can monitor its parent, itself, and its immediate children.

Return the minimum number of cameras needed to monitor all nodes of the tree.

 

Example 1:

Input: root = [0,0,null,0,0]
Output: 1
Explanation: One camera is enough to monitor all nodes if placed as shown.

Example 2:

Input: root = [0,0,null,0,null,0,null,null,0]
Output: 2
Explanation: At least two cameras are needed to monitor all nodes of the tree. The above image shows one of the valid configurations of camera placement.

 

Constraints:

    The number of nodes in the tree is in the range [1, 1000].
    Node.val == 0


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
    int greedy(TreeNode* root) {
        int ans = 0;
        std::unordered_set<TreeNode*> covered;
        covered.insert(nullptr);

        std::function<void(TreeNode*, TreeNode*)> recurr = [&](TreeNode* now, TreeNode* pre) {
            if (now == nullptr) {
                return;
            }

            recurr(now->left, now);
            recurr(now->right, now);

            if ((pre == nullptr && covered.find(now) == covered.end()) || 
                    covered.find(now->left) == covered.end() || covered.find(now->right) == covered.end()) {

                ++ans;
                covered.insert(now);
                covered.insert(pre);
                covered.insert(now->left);
                covered.insert(now->right);
            }
        };

        recurr(root, nullptr);
        return ans;
    }

    int recursive(TreeNode* root) {

        std::function<std::vector<int>(TreeNode*)> recurr = [&](TreeNode* now) -> std::vector<int> {
            if (now == nullptr) {
                return {0, 0, 99999};
            }

            std::vector<int> L = recurr(now->left);
            std::vector<int> R = recurr(now->right);
            int minL12 = std::min(L[1], L[2]);
            int minR12 = std::min(R[1], R[2]);

            int s0 = L[1] + R[1];
            int s1 = std::min(L[2] + minR12, R[2] + minL12);
            int s2 = 1 + std::min(L[0], minL12) + std::min(R[0], minR12);

            return {s0, s1, s2};
        };

        std::vector<int> ans = recurr(root);

        return std::min(ans[1], ans[2]);
    }
public:
    int minCameraCover(TreeNode* root) {
        //return recursive(root);
        return greedy(root);
    }
};