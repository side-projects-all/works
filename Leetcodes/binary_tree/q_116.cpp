/*
You are given a perfect binary tree where all leaves are on the same level, and every parent has two children. The binary tree has the following definition:

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

 

Example 1:

Input: root = [1,2,3,4,5,6,7]
Output: [1,#,2,3,#,4,5,6,7,#]
Explanation: Given the above perfect binary tree (Figure A), your function should populate each next pointer to point to its next right node, just like in Figure B. The serialized output is in level order as connected by the next pointers, with '#' signifying the end of each level.

Example 2:

Input: root = []
Output: []

 

Constraints:

    The number of nodes in the tree is in the range [0, 2^12 - 1].
    -1000 <= Node.val <= 1000

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
        //return byLevelOrderTravel(root);
    }

private:
    //std::queue<Node*> q;
    //int count;
    Node* p_root;

    //using the idea of linked list
    Node* byNext(Node* now) {
        p_root = now;

        Node* leftMost = p_root;
        Node* head = NULL;
        //while moving to leaf level, we finished
        while(leftMost->left != NULL) {
            head = leftMost;

            //iterate the linked list
            while (head != NULL) {
                
                //connect own children
                //through this connection, we could iterate those inner nodes
                head->left->next = head->right;

                //connect children from different root
                if (head->next != NULL) {
                    head->right->next = head->next->left;
                }

                //to the sibling
                head = head->next;
            }

            //to the next level
            leftMost = leftMost->left;
        }

        return p_root;
    }

    /*
    Node* byLevelOrderTravel(Node* now) {
        //insert children of root
        p_root = now;
        //set root right node NULL
        p_root->next = NULL;

        q.push(now->left);
        q.push(now->right);

        //loop through the queue
        int i = 0;
        while(!q.empty()) {

            count = q.size();
            for (i = 0; i < count; ++i) {
                now = q.front();
                q.pop();

                if (i < count - 1) {
                    now->next = q.front();
                }


                if (now->left != NULL) {
                    q.push(now->left);
                }
                if (now->right != NULL) {
                    q.push(now->right);
                }

            }

        }

        return p_root;
    }
    */
};