/*
Given a non-negative integer represented as a linked list of digits, plus one to the integer.

The digits are stored such that the most significant digit is at the head of the list.

 

Example 1:

Input: head = [1,2,3]
Output: [1,2,4]

Example 2:

Input: head = [0]
Output: [1]

 

Constraints:

    The number of nodes in the linked list is in the range [1, 100].
    0 <= Node.val <= 9
    The number represented by the linked list does not contain leading zeros except for the zero itself. 


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
class Solution {
private:
    int recursion(ListNode* now) {
        if (now == nullptr) {
            return 1;
        }

        int val = now->val + recursion(now->next);
        now->val = val % 10;

        return val / 10;
    }
    ListNode* by_recursion(ListNode* head) {
        ListNode* now = head;

        int final_carray = recursion(now);
        if (final_carray) {
            ListNode* new_head = new ListNode(1, head);

            return new_head;
        }

        return head;
    }
public:
    ListNode* plusOne(ListNode* head) {
        return by_recursion(head);
    }
};