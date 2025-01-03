/*
You are given the root of a binary tree with n nodes. Each node is assigned a unique value from 1 to n. You are also given an array queries of size m.

You have to perform m independent queries on the tree where in the ith query you do the following:

    Remove the subtree rooted at the node with the value queries[i] from the tree. It is guaranteed that queries[i] will not be equal to the value of the root.

Return an array answer of size m where answer[i] is the height of the tree after performing the ith query.

Note:

    The queries are independent, so the tree returns to its initial state after each query.
    The height of a tree is the number of edges in the longest simple path from the root to some node in the tree.

 

Example 1:

Input: root = [1,3,4,2,null,6,5,null,null,null,null,null,7], queries = [4]
Output: [2]
Explanation: The diagram above shows the tree after removing the subtree rooted at node with value 4.
The height of the tree is 2 (The path 1 -> 3 -> 2).

Example 2:

Input: root = [5,8,9,2,1,3,7,4,6], queries = [3,2,4,8]
Output: [3,2,3,2]
Explanation: We have the following queries:
- Removing the subtree rooted at node with value 3. The height of the tree becomes 3 (The path 5 -> 8 -> 2 -> 4).
- Removing the subtree rooted at node with value 2. The height of the tree becomes 2 (The path 5 -> 8 -> 1).
- Removing the subtree rooted at node with value 4. The height of the tree becomes 3 (The path 5 -> 8 -> 2 -> 6).
- Removing the subtree rooted at node with value 8. The height of the tree becomes 2 (The path 5 -> 9 -> 3).

 

Constraints:

    The number of nodes in the tree is n.
    2 <= n <= 10^5
    1 <= Node.val <= n
    All the values in the tree are unique.
    m == queries.length
    1 <= m <= min(n, 10^4)
    1 <= queries[i] <= n
    queries[i] != root.val


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
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        return by_two_traversal(root, queries);
    }
private:
    int max_height[100001];
    int curr_max_height{ 0 };
    vector<int> by_two_traversal(TreeNode* root, vector<int>& queries) {
        go_left_to_right(root, 0);
        curr_max_height = 0;
        go_right_to_left(root, 0);

        int len = queries.size();
        std::vector<int> ans(len);
        for (int i = 0; i < len; ++i) {
            ans[i] = max_height[queries[i]];
        }

        return ans;
    }

    void go_left_to_right(TreeNode* node, int curr_height) {
        if (node == nullptr) {
            return;
        }

        max_height[node->val] = curr_max_height;
        curr_max_height = std::max(curr_max_height, curr_height);

        go_left_to_right(node->left, curr_height + 1);
        go_left_to_right(node->right, curr_height + 1);
    }

    void go_right_to_left(TreeNode* node, int curr_height) {
        if (node == nullptr) {
            return;
        }

        max_height[node->val] = std::max(max_height[node->val], curr_max_height);
        curr_max_height = std::max(curr_max_height, curr_height);
        
        go_right_to_left(node->right, curr_height + 1);
        go_right_to_left(node->left, curr_height + 1);
    }
};