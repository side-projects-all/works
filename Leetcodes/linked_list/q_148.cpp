/*
Given the head of a linked list, return the list after sorting it in ascending order.

 

Example 1:

Input: head = [4,2,1,3]
Output: [1,2,3,4]

Example 2:

Input: head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]

Example 3:

Input: head = []
Output: []

 

Constraints:

    The number of nodes in the list is in the range [0, 5 * 10^4].
    -10^5 <= Node.val <= 10^5

 

Follow up: Can you sort the linked list in O(n logn) time and O(1) memory (i.e. constant space)?

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
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(-1);
        ListNode* tail = dummy;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;

            } else {
                tail->next = l2;
                l2 = l2->next;
            }

            tail = tail->next;
        }

        tail->next = l1 == nullptr ? l2 : l1;

        return dummy->next;
    }
    ListNode* merge_sort(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        //find mid
        ListNode* fast = head->next;    //important!
        ListNode* slow = head;
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }

        ListNode* mid = slow->next;
        slow->next = nullptr;
        ListNode* left = merge_sort(head);
        ListNode* right = merge_sort(mid);

        //merge
        return merge(left, right);
    }
    ListNode* by_merge_sort(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        
        return merge_sort(head);
    }
public:
    ListNode* sortList(ListNode* head) {
        return by_merge_sort(head);
    }
};
