/*
Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

 

Example 1:

Input: head = [1,4,3,2,5,2], x = 3
Output: [1,2,2,4,3,5]

Example 2:

Input: head = [2,1], x = 2
Output: [1,2]

 

Constraints:

    The number of nodes in the list is in the range [0, 200].
    -100 <= Node.val <= 100
    -200 <= x <= 200


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
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* s = nullptr;
        ListNode* b = nullptr;
        ListNode** b_now = &b;
        ListNode** s_now = &s;
        ListNode*** ptr;
        while (head) {
            ptr = (head->val < x) ? &s_now : &b_now;
            **ptr = head;
            *ptr = &(**ptr)->next;
            /*
            if (head->val < x) {
                *s_now = head;
                s_now = &(*s_now)->next;
            } else {
                *b_now = head;
                b_now = &(*b_now)->next;
            }
            */
            head = head->next;
        }

        *s_now = b;
        *b_now = nullptr;
        return s;
    }
};
