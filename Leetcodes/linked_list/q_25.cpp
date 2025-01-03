/*
Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.

You may not alter the values in the list's nodes, only nodes themselves may be changed.

 

Example 1:

Input: head = [1,2,3,4,5], k = 2
Output: [2,1,4,3,5]

Example 2:

Input: head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]

 

Constraints:

    The number of nodes in the list is n.
    1 <= k <= n <= 5000
    0 <= Node.val <= 1000

 
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
    ListNode* reverse(ListNode* head, int k) {
        ListNode* new_head = nullptr;
        ListNode* now = head;

        while (k > 0) {
            ListNode* next_n = now->next;

            now->next = new_head;
            new_head = now;

            now = next_n;
            --k;
        }

        return new_head;
    }

    ListNode* iterative(ListNode* head, int k) {
        ListNode* now = head;
        ListNode* k_end = nullptr;
        ListNode* new_head = nullptr;

        while (now != nullptr) {
            int cnt = 0;
            now = head;

            while (cnt < k && now != nullptr) {
                now = now->next;
                ++cnt;
            }

            if (cnt == k) {
                ListNode* rev_head = reverse(head, k);

                //setting head to initially reversed list
                if (new_head == nullptr) {
                    new_head = rev_head;
                }

                if (k_end != nullptr) {
                    k_end->next = rev_head;
                }

                k_end = head;
                head = now;
            }

        }

        if (k_end != nullptr) {
            k_end->next = head;
        }

        return new_head == nullptr ? head : new_head;
    }

    ListNode* recursive(ListNode* head, int k) {
        ListNode* now = head;
        int cnt = 0;

        while (cnt < k && now != nullptr) {
            now = now->next;
            ++cnt;
        }

        if (cnt == k) {
            ListNode* rev_head = reverse(head, k);
            head->next = recursive(now, k);

            return rev_head;
        }

        return head;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        //return recursive(head, k);
        return iterative(head, k);
    }
};