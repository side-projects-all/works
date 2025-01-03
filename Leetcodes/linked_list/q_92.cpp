/*
Given the head of a singly linked list and two integers left and right where left <= right, reverse the nodes of the list from position left to position right, and return the reversed list.

 

Example 1:

Input: head = [1,2,3,4,5], left = 2, right = 4
Output: [1,4,3,2,5]

Example 2:

Input: head = [5], left = 1, right = 1
Output: [5]

 

Constraints:

    The number of nodes in the list is n.
    1 <= n <= 500
    -500 <= Node.val <= 500
    1 <= left <= right <= n

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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        int cnt = 1;
        
        ListNode* now = head;
        std::deque<ListNode*> dq;
        
        while (cnt < left) {
            now = now->next;
            ++cnt;
        }
        dq.push_back(now);

        while (cnt < right) {
            now = now->next;
            dq.push_back(now);
            ++cnt;
        }
        
        while (dq.size() > 1) {
            ListNode* L = dq.front();
            ListNode* R = dq.back();
            dq.pop_front();
            dq.pop_back();

            int tmp = L->val;
            L->val = R->val;
            R->val = tmp;
        }

        return head;
    }
};