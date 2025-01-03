/*
Given an n-ary tree, return the level order traversal of its nodes' values.

Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).

 

Example 1:

Input: root = [1,null,3,2,4,null,5,6]
Output: [[1],[3,2,4],[5,6]]

Example 2:

Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]

 

Constraints:

    The height of the n-ary tree is less than or equal to 1000
    The total number of nodes is between [0, 104]


*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        std::vector<std::vector<int>> result;

        if (root == NULL) {
            return result;
        }
        
        std::queue<Node*> q;
        q.push(root);
        int currLevel_len = 1;
        Node* curr = NULL;
        while (!q.empty()) {

            std::vector<int> values;
            int childrenLevel_len = 0;
            for (int i = 0; i < currLevel_len; ++i) {
                curr = q.front();
                q.pop();
                values.push_back(curr->val);
                childrenLevel_len += curr->children.size();

                for (int j = 0; j < curr->children.size(); ++j) {
                    q.push(curr->children[j]);
                }
            }

            result.push_back(values);
            currLevel_len = childrenLevel_len;
        }

        return result;
    }
};