/*
Implement the BSTIterator class that represents an iterator over the in-order traversal of a binary search tree (BST):

    BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. The root of the BST is given as part of the constructor. The pointer should be initialized to a non-existent number smaller than any element in the BST.
    boolean hasNext() Returns true if there exists a number in the traversal to the right of the pointer, otherwise returns false.
    int next() Moves the pointer to the right, then returns the number at the pointer.

Notice that by initializing the pointer to a non-existent smallest number, the first call to next() will return the smallest element in the BST.

You may assume that next() calls will always be valid. That is, there will be at least a next number in the in-order traversal when next() is called.

 

Example 1:

Input
["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
[[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
Output
[null, 3, 7, true, 9, true, 15, true, 20, false]

Explanation
BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
bSTIterator.next();    // return 3
bSTIterator.next();    // return 7
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 9
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 15
bSTIterator.hasNext(); // return True
bSTIterator.next();    // return 20
bSTIterator.hasNext(); // return False

 

Constraints:

    The number of nodes in the tree is in the range [1, 10^5].
    0 <= Node.val <= 10^6
    At most 10^5 calls will be made to hasNext, and next.

 

Follow up:

    Could you implement next() and hasNext() to run in average O(1) time and use O(h) memory, where h is the height of the tree?


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
class BSTIterator {
private: 
    //TreeNode* inorder_root;
    //std::vector<TreeNode*> list;
    //int i = 0;
    /*
    void inorder(TreeNode* p_root) {
        if (p_root == nullptr) {
            return;
        }

        inorder(p_root->left);
        list.push_back(p_root);
        inorder(p_root->right);
    }*/

    void inorder_left(TreeNode* p_root) {
        TreeNode* now = p_root;
        s.push(now);

        while (now->left != nullptr) {
            s.push(now->left);

            now = now->left;
        }
    }

    std::stack<TreeNode*> s;

public:
    BSTIterator(TreeNode* root) {

        inorder_left(root);

        //inorder(root);
    }
    
    int next() {
        /*
        int index = i;
        ++i;

        return list[index]->val;
        */
        TreeNode* now = s.top();
        s.pop();

        if (now->right != nullptr) {
            inorder_left(now->right);
        }

        return now->val;
    }
    
    bool hasNext() {
        /*
        if (i == list.size()) {
            return false;
        }

        return true;
        */

        return !s.empty();
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */