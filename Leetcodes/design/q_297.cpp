/*
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

Clarification: The input/output format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

 

Example 1:

Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]

Example 2:

Input: root = []
Output: []

 

Constraints:

    The number of nodes in the tree is in the range [0, 10^4].
    -1000 <= Node.val <= 1000


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
    void append(TreeNode* root, std::string& s) {
        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* n = q.front();
            q.pop();

            if (n == nullptr) {
                s.push_back('N');

            } else {
                s += std::to_string(n->val);    //it might be negative or several digits
                q.push(n->left);
                q.push(n->right);
            }

            s.push_back('>');
        }
    }

    TreeNode* get_node(std::string& s, int& i) {
        if (i >= s.size() || s[i] == 'N') {
            i += 2;
            return nullptr;
        }

        int sign = 1;
        if (s[i] == '-') {
            sign = -1;
            ++i;
        }

        int val = 0;
        while (s[i] != '>') {
            val = val * 10 + (s[i] - '0');
            ++i;
        }

        val *= sign;
        ++i;

        return new TreeNode(val);
    }
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        std::string s{""};
        append(root, s);

        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int i = 0;
        TreeNode* root = get_node(data, i);
        if (root == nullptr) {
            return root;
        }

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* n = q.front();
            q.pop();

            n->left = get_node(data, i); 
            n->right = get_node(data, i);

            if (n->left != nullptr) {
                q.push(n->left);
            }

            if (n->right != nullptr) {
                q.push(n->right);
            }
        }

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
