/*
Given the head of a linked list, rotate the list to the right by k places.

 

Example 1:

Input: head = [1,2,3,4,5], k = 2
Output: [4,5,1,2,3]

Example 2:

Input: head = [0,1,2], k = 4
Output: [2,0,1]

 

Constraints:

    The number of nodes in the list is in the range [0, 500].
    -100 <= Node.val <= 100
    0 <= k <= 2 * 10^9


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
    ListNode* rotateRight(ListNode* head, int k) {
        //empty case, or one node case, or k is zero case
        if (head == NULL || head->next == NULL || k == 0) { 
            return head;
        }
        
        ListNode* now = head;
        ListNode* newHead = NULL;
        int len = 1;
        
        //find tail and calculate length
        while (now->next != NULL) {
            now = now->next;
            ++len;
        }
        
        //connet tail and head
        now->next = head;
        
        //new tail position
        int newTailPos = len - (k % len) - 1;
        
        now = head;
        //move to new tail
        for (int i = 0; i < newTailPos; ++i) {
            now = now->next;
        }
        
        newHead = now->next;
        now->next = NULL;
        
        return newHead;
    }
};