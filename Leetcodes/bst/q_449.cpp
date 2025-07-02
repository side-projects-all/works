/*
Serialization is converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary search tree. There is no restriction on how your serialization/deserialization algorithm should work. You need to ensure that a binary search tree can be serialized to a string, and this string can be deserialized to the original tree structure.

The encoded string should be as compact as possible.

 

Example 1:

Input: root = [2,1,3]
Output: [2,1,3]

Example 2:

Input: root = []
Output: []

 

Constraints:

    The number of nodes in the tree is in the range [0, 10^4].
    0 <= Node.val <= 10^4
    The input tree is guaranteed to be a binary search tree.


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
class Codec {
private:
    void dfs_encode(TreeNode* root, std::string& s) {
        if (root == nullptr) {
            return;
        }

        dfs_encode(root->left, s);
        dfs_encode(root->right, s);

        s += std::to_string(root->val) + ",";
    }

    TreeNode* dfs_decode(std::vector<int>& vals, int left, int right) {
        if (vals.empty()) {
            return nullptr;
        }

        int val = vals.back();
        if (val < left || val > right) {
            return nullptr;
        }

        vals.pop_back();
        TreeNode* root = new TreeNode(val);
        root->right = dfs_decode(vals, val, right);
        root->left = dfs_decode(vals, left, val);

        return root;
    }
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) {
            return "";
        }

        std::string s;
        dfs_encode(root, s);

        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) {
            return nullptr;
        }

        std::vector<int> vals;
        std::string tmp;
        std::istringstream iss(data);
        while (std::getline(iss, tmp, ',')) {
            vals.push_back(std::stoi(tmp));
        }

        return dfs_decode(vals, INT_MIN, INT_MAX);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;