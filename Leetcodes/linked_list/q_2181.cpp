/*
You are given the head of a linked list, which contains a series of integers separated by 0's. The beginning and end of the linked list will have Node.val == 0.

For every two consecutive 0's, merge all the nodes lying in between them into a single node whose value is the sum of all the merged nodes. The modified list should not contain any 0's.

Return the head of the modified linked list.

 

Example 1:

Input: head = [0,3,1,0,4,5,2,0]
Output: [4,11]
Explanation: 
The above figure represents the given linked list. The modified list contains
- The sum of the nodes marked in green: 3 + 1 = 4.
- The sum of the nodes marked in red: 4 + 5 + 2 = 11.

Example 2:

Input: head = [0,1,0,3,0,2,2,0]
Output: [1,3,4]
Explanation: 
The above figure represents the given linked list. The modified list contains
- The sum of the nodes marked in green: 1 = 1.
- The sum of the nodes marked in red: 3 = 3.
- The sum of the nodes marked in yellow: 2 + 2 = 4.

 

Constraints:

    The number of nodes in the list is in the range [3, 2 * 10^5].
    0 <= Node.val <= 1000
    There are no two consecutive nodes with Node.val == 0.
    The beginning and end of the linked list have Node.val == 0.


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
    ListNode* fast_slow_ptr(ListNode* head) {
        int sum = 0;
        ListNode* fast = head->next;
        ListNode* slow = head;
        ListNode* last = nullptr;

        while (fast) {

            if (fast->val != 0) {
                sum += fast->val;

            } else {
                slow->val = sum;
                last = slow;
                slow = slow->next;
                sum = 0;
            }

            fast = fast->next;
        }

        last->next = nullptr;
        return head;
    }
    ListNode* my_naive(ListNode* head) {
        ListNode* now = head;
        ListNode* new_list = new ListNode();
        ListNode* vals_sum = new_list;

        while (now != nullptr) {

            if (now->val != 0) {
                ListNode* b = now;
                int sum = 0;
                while (b->val != 0) {
                    sum += b->val;
                    b = b->next;
                }

                vals_sum->val = sum;
                if (b->next != nullptr) {
                    vals_sum->next = new ListNode();
                    vals_sum = vals_sum->next;
                }
                
                now = b;
            } else {
                now = now->next;
            }
        }

        return new_list;
    }

public:
    ListNode* mergeNodes(ListNode* head) {
        //return my_naive(head);
        
        return fast_slow_ptr(head);
    }
};