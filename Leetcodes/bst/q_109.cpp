/*
Given the head of a singly linked list where elements are sorted in ascending order, convert it to a
height-balanced
binary search tree.

 

Example 1:

Input: head = [-10,-3,0,5,9]
Output: [0,-3,9,-10,null,5]
Explanation: One possible answer is [0,-3,9,-10,null,5], which represents the shown height balanced BST.

Example 2:

Input: head = []
Output: []

 

Constraints:

    The number of nodes in head is in the range [0, 2 * 10^4].
    -10^5 <= Node.val <= 10^5


*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
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
private:
    //TreeNode* recursion(int l, int r, ListNode*& head) {
    TreeNode* recursion(int l, int r, ListNode*&& head) {
        if (l > r) {
            return nullptr;
        }

        int mid = l + (r - l) / 2;
        //TreeNode* left = recursion(l, mid - 1, head);
        TreeNode* left = recursion(l, mid - 1, std::move(head));

        TreeNode* now = new TreeNode(head->val);
        now->left = left;

        head = head->next;
        //now->right = recursion(mid + 1, r, head);
        now->right = recursion(mid + 1, r, std::move(head));

        return now;
    }
    TreeNode* by_recursion(ListNode* head) {
        int len = 0;
        ListNode* tmp = head;
        while (tmp != nullptr) {
            tmp = tmp->next;
            ++len;
        }

        //return recursion(0, len - 1, head);
        return recursion(0, len - 1, std::move(head));
    }
public:
    TreeNode* sortedListToBST(ListNode* head) {
        return by_recursion(head);
    }
};