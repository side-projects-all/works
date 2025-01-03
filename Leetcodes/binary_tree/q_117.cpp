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


// Definition for a Node.
/*
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
public:
    Node* connect(Node* root) {
        if (root == NULL) {
            return NULL;
        }

        if (root->left == NULL && root->right == NULL) {
            return root;
        }

        return byNext(root);
    }

private:
    Node* p_root;
    Node* prev;
    Node* leftMost;

    void processChild(Node* child) {
        if (child != NULL) {
            if (prev != NULL) {
                prev->next = child;
            } else {
                //this is for the condition we find first child
                leftMost = child;
            }

            prev = child;
        }
    }

    //using the idea of linked list
    Node* byNext(Node* now) {
        p_root = now;

        leftMost = p_root;
        Node* curr = leftMost;

        //while moving to leaf level, we finished
        while(leftMost != NULL) {
            
            //for the latest node on the "next" level
            prev = NULL;

            //head for the latest node on current level 
            curr = leftMost;

            //reset the leftMost
            leftMost = NULL;

            //iterate the linked list
            while (curr != NULL) {
                
                processChild(curr->left);
                processChild(curr->right);

                //to the sibling
                curr = curr->next;
            }

        }

        return p_root;
    }

};