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
        ListNode* less = new ListNode();
        ListNode* bigger = new ListNode();

        ListNode* less_now = less;
        ListNode* big_now = bigger;
        ListNode* now = head;

        while (now != nullptr) {
            if (now->val < x) {
                less_now->next = now;
                less_now = less_now->next;

            } else {
                big_now->next = now;
                big_now = big_now->next;
            }

            now = now->next;
        }

        less_now->next = bigger->next;
        big_now->next = nullptr;

        return less->next;
    }
};
