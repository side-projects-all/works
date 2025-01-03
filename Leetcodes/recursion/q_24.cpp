/*
Given a linked list, swap every two adjacent nodes and return its head. You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)

 

Example 1:

Input: head = [1,2,3,4]
Output: [2,1,4,3]

Example 2:

Input: head = []
Output: []

Example 3:

Input: head = [1]
Output: [1]

 

Constraints:

    The number of nodes in the list is in the range [0, 100].
    0 <= Node.val <= 100


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
    ListNode* swapPairs(ListNode* head) {
        //begin = head;
        //return swapper(NULL, head);
        return swapper2(head);
    }
private:
    ListNode* swapper2(ListNode* starter) {
        if (starter == NULL || starter->next == NULL) {
            return starter;
        }

        ListNode* tmp = starter;
        ListNode* tmp_next = starter->next;

        tmp->next = swapper2(tmp_next->next);
        tmp_next->next = tmp;

        return tmp_next;
    }
    /*
    ListNode* swapper(ListNode* pre, ListNode* starter) {
        
        //the critical point here is when you do following swap, 
        //the pre node should also change its next
        

        if (starter == NULL || starter->next == NULL) {
            return begin;
        }
        
        ListNode* tmp = starter;
        ListNode* tmp_next = starter->next;
        ListNode* tmp_next_next = starter->next->next;
        tmp->next = tmp_next_next;
        tmp_next->next = tmp;
        
        if (pre != NULL) {
            pre->next = tmp_next;
        }
        
        if (change_head) {
            begin = tmp_next;
            change_head = false;
        }

        return swapper(tmp, tmp_next_next);
    }*/

    //ListNode* begin = NULL;
    //bool change_head = true;
};