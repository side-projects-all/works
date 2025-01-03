/*
Given the root of a binary tree, return all duplicate subtrees.

For each kind of duplicate subtrees, you only need to return the root node of any one of them.

Two trees are duplicate if they have the same structure with the same node values.

 

Example 1:

Input: root = [1,2,3,4,null,2,4,null,null,4]
Output: [[2,4],[4]]

Example 2:

Input: root = [2,1,1]
Output: [[1]]

Example 3:

Input: root = [2,2,2,3,null,3,null]
Output: [[2,3],[3]]

 

Constraints:

    The number of the nodes in the tree will be in the range [1, 5000]
    -200 <= Node.val <= 200


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
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        
        serialize(root);
        return ans;
    }
    
private:
    std::unordered_map<std::string, int> counts;
    std::vector<TreeNode*> ans;
    
    std::string serialize(TreeNode* curr) {
        if (curr == NULL) {
            return "";
        }
        
        //serialize every subtree to make a key
        std::string key = std::to_string(curr->val) + "," +
                          serialize(curr->left) + "," +
                          serialize(curr->right);
        
        //check if key existed, if not, insert it, else add numbers
        if (counts.find(key) == counts.end()) {
            counts.insert(std::make_pair(key, 1));
            
        } else {
            ++counts[key];
        }
        
        //check if counts of the key equals to 2, if it were, insert into ans
        if (counts[key] == 2) {
            ans.push_back(curr);
        }
        
        return key;
    }
};