/*
You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

 

Example 1:

Input: l1 = [7,2,4,3], l2 = [5,6,4]
Output: [7,8,0,7]

Example 2:

Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [8,0,7]

Example 3:

Input: l1 = [0], l2 = [0]
Output: [0]

 

Constraints:

    The number of nodes in each linked list is in the range [1, 100].
    0 <= Node.val <= 9
    It is guaranteed that the list represents a number that does not have leading zeros.

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
        ListNode* now = head;
        ListNode* prev = nullptr;

        while (now != nullptr) {
            ListNode* tmp = now->next;
            now->next = prev;
            prev = now;
            now = tmp;
        }

        return prev;
    }
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* r1 = reverse_list(l1);
        ListNode* r2 = reverse_list(l2);

        ListNode* merged = new ListNode(0);
        ListNode* curr = merged;

        int carry = 0;

        while (true) {
            int sum = carry;

            if (r1 != nullptr) {
                sum += r1->val;
            }

            if (r2 != nullptr) {
                sum += r2->val;
            }

            carry = sum / 10;
            sum %= 10;

            curr->val = sum;

            if (r1 != nullptr) {
                r1 = r1->next;
            }

            if (r2 != nullptr) {
                r2 = r2->next;
            }

            if (r1 == nullptr && r2 == nullptr && carry == 0) {
                break;
            }

            curr->next = new ListNode();
            curr = curr->next;
        }

        ListNode* rev = reverse_list(merged);
        return rev;
    }
};