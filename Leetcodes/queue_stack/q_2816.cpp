/*
You are given the head of a non-empty linked list representing a non-negative integer without leading zeroes.

Return the head of the linked list after doubling it.

 

Example 1:

Input: head = [1,8,9]
Output: [3,7,8]
Explanation: The figure above corresponds to the given linked list which represents the number 189. Hence, the returned linked list represents the number 189 * 2 = 378.

Example 2:

Input: head = [9,9,9]
Output: [1,9,9,8]
Explanation: The figure above corresponds to the given linked list which represents the number 999. Hence, the returned linked list reprersents the number 999 * 2 = 1998. 

 

Constraints:

    The number of nodes in the list is in the range [1, 10^4]
    0 <= Node.val <= 9
    The input is generated such that the list represents a number that does not have leading zeros, except the number 0 itself.


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
    ListNode* reverse_list(ListNode* head) {
        ListNode* curr = head;
        ListNode* prev = nullptr;
        ListNode* next_node = nullptr;

        while (curr != nullptr) {
            next_node = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next_node;
        }

        return prev;
    }
public:
    ListNode* doubleIt(ListNode* head) {
        ListNode* r_head = reverse_list(head);
        ListNode* curr = r_head;
        ListNode* prev = curr;

        int carry = 0;
        while (curr != nullptr) {

            int doubled = curr->val * 2 + carry;
            if (doubled >= 10) {
                curr->val = (doubled - 10);
                carry = 1;

            } else {
                curr->val = doubled;
                carry = 0;
            }

            prev = curr;
            curr = curr->next;
        }

        if (carry == 1) {
            ListNode* carry_node = new ListNode(1);
            prev->next = carry_node;
        }

        return reverse_list(r_head);
    }
};