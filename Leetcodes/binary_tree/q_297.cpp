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
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {

        std::string str = "";
        serializeTree(root, str);
        return str;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        std::queue<std::string> splited = split(data, ",");
        
        return deserializeString(splited);
    }

private:
    void serializeTree(TreeNode* root, std::string &str) {
        
        if (root == NULL) {
            str += "null,";
            return;

        } else {
            str += std::to_string(root->val) + ",";
            serializeTree(root->left, str);
            serializeTree(root->right, str);
        }
    }

    TreeNode* deserializeString(std::queue<std::string> &splited) {
        
        std::string first = splited.front();
        splited.pop();
        //empty
        if (first.compare("null") == 0) {
            return NULL;
        }

        TreeNode* root = new TreeNode(std::stoi(first));
        root->left = deserializeString(splited);
        root->right = deserializeString(splited);

        return root;
    }

    std::queue<std::string> split(const std::string &str, const std::string& pattern) {
        std::queue<std::string> result;

        std::string::size_type begin;
        std::string::size_type end;

        end = str.find(pattern);
        begin = 0;

        while (end != std::string::npos) {
          if (end - begin != 0) {
            result.push(str.substr(begin, end - begin)); 
          }    

          begin = end + pattern.size();
          end = str.find(pattern, begin);
        }

        if (begin != str.length()) {
          result.push(str.substr(begin));
        }

        return result;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));