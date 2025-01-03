/*
Given the head of a singly linked list, reverse the list, and return the reversed list.


Example 1:

Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]

Example 2:

Input: head = [1,2]
Output: [2,1]

Example 3:

Input: head = []
Output: []

 

Constraints:

    The number of nodes in the list is the range [0, 5000].
    -5000 <= Node.val <= 5000


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
    ListNode* reverseList(ListNode* head) {
        return iterative(head);
        //recursive(head);
        //return p_head;
    }

private:
    ListNode* p_head;
    ListNode* recursive(ListNode* now) {
        if (now == NULL) {
            return now;
        }

        if (now != NULL && now->next == NULL) {
            p_head = now;
            return now;
        }

        ListNode* pre = recursive(now->next);
        pre->next = now;
        now->next = NULL;

        return now;
    }

    ListNode* iterative(ListNode* head) {
        ListNode* now = head;
        ListNode* prev = nullptr;

        while (now != nullptr) {
            ListNode* tmp = now->next;
            now->next = prev;
            prev = now;
            now = tmp;
        }

        return prev;
        /*
        ListNode* now = head;
        ListNode* nextNode = NULL;
        ListNode* prevNode = NULL;
        
        while(now != NULL) {
            nextNode = now->next;
            now->next = prevNode;
            prevNode = now;
            now = nextNode;

        }
        
        return prevNode;
        */
    }
};