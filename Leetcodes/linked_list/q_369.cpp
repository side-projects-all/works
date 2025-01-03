/*
Given a non-negative integer represented as a linked list of digits, plus one to the integer.

The digits are stored such that the most significant digit is at the head of the list.

 

Example 1:

Input: head = [1,2,3]
Output: [1,2,4]

Example 2:

Input: head = [0]
Output: [1]

 

Constraints:

    The number of nodes in the linked list is in the range [1, 100].
    0 <= Node.val <= 9
    The number represented by the linked list does not contain leading zeros except for the zero itself. 


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
    ListNode* byStack(ListNode* head) {

        int carry = 0;
        bool reverseNow = false;
        std::stack<ListNode*> s;
        s.push(head);

        while (!s.empty()) {
            ListNode* n = s.top();

            if (n->next != nullptr && !reverseNow) {
                s.push(n->next);
                continue;
            }

            s.pop();
            reverseNow = true;

            int val = (n->next == nullptr) ? n->val + 1 : n->val + carry;

            carry = val / 10;
            val = val % 10;
            
            n->val = val;
        }

        if (carry == 1) {
            ListNode* n = head;
            head = new ListNode(1, head);
        }

        return head;
    }
public:
    ListNode* plusOne(ListNode* head) {
        return byStack(head);

    }
};