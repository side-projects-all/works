/*
Given a binary tree

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

 

Example 1:

Input: root = [1,2,3,4,5,null,7]
Output: [1,#,2,3,#,4,5,7,#]
Explanation: Given the above binary tree (Figure A), your function should populate each next pointer to point to its next right node, just like in Figure B. The serialized output is in level order as connected by the next pointers, with '#' signifying the end of each level.

Example 2:

Input: root = []
Output: []

 

Constraints:

    The number of nodes in the tree is in the range [0, 6000].
    -100 <= Node.val <= 100

*/


/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
private:
    Node* by_bfs(Node* root) {
        if (root == nullptr || (root->left == nullptr && root->right == nullptr)) {
            return root;
        }

        Node* parent = root;
        Node* prev = nullptr;
        Node* now = root;
        std::function<void(Node*)> do_child = [&parent, &prev](Node* child) {

            if (child != nullptr) {

                if (prev != nullptr) {
                    prev->next = child;

                } else {
                    parent = child;
                }

                prev = child;
            }
        };
        
        while (parent != nullptr) {
            now = parent;
            prev = nullptr;
            parent = nullptr;

            while (now != nullptr) {

                do_child(now->left);
                do_child(now->right);
                
                now = now->next;
            }
        }

        return root;
    }
public:
    Node* connect(Node* root) {
        return by_bfs(root);
    }
};