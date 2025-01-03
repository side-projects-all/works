/*
Given the head of a singly linked list, return true if it is a palindrome.

 
Example 1:

Input: head = [1,2,2,1]
Output: true

Example 2:

Input: head = [1,2]
Output: false

 

Constraints:

    The number of nodes in the list is in the range [1, 10^5].
    0 <= Node.val <= 9

Follow up: Could you do it in O(n) time and O(1) space?

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
    bool isPalindrome(ListNode* head) {
        if (head->next == nullptr) {
            return true;
        }

        left_pole = head;
        return recursive(head);
    }

private:
    ListNode* left_pole;
    bool recursive(ListNode* right_pole) {
        if (right_pole == nullptr) {
            return true;
        }

        if (!recursive(right_pole->next)) {
            return false;
        }

        if (right_pole->val != left_pole->val) {
            return false;
        }

        left_pole = left_pole->next;

        return true;
    }
};