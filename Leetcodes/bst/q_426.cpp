/*
Convert a Binary Search Tree to a sorted Circular Doubly-Linked List in place.

You can think of the left and right pointers as synonymous to the predecessor and successor pointers in a doubly-linked list. For a circular doubly linked list, the predecessor of the first element is the last element, and the successor of the last element is the first element.

We want to do the transformation in place. After the transformation, the left pointer of the tree node should point to its predecessor, and the right pointer should point to its successor. You should return the pointer to the smallest element of the linked list.

 

Example 1:

Input: root = [4,2,5,1,3]


Output: [1,2,3,4,5]

Explanation: The figure below shows the transformed BST. The solid line indicates the successor relationship, while the dashed line means the predecessor relationship.

Example 2:

Input: root = [2,1,3]
Output: [1,2,3]

 

Constraints:

    The number of nodes in the tree is in the range [0, 2000].
    -1000 <= Node.val <= 1000
    All the values of the tree are unique.


*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/

class Solution {
private:
    void inorder(Node* root, Node *&prev, Node *&first) {
        if (root == nullptr) {
            return;
        }

        inorder(root->left, prev, first);

        if (prev != nullptr) {
            prev->right = root;
            root->left = prev;
        } else {
            first = root;
        }

        prev = root;

        inorder(root->right, prev, first);
    }
    Node* by_inorder(Node* root) {
        if (root == nullptr) {
            return root;
        }

        Node* first = nullptr;
        Node* last = nullptr;
        inorder(root, last, first);

        last->right = first;
        first->left = last;
        
        return first;
    }
public:
    Node* treeToDoublyList(Node* root) {
        return by_inorder(root);
    }
};