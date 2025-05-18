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
private:
    ListNode* from_left;
    bool recursive(ListNode* curr) {
        if (curr == nullptr) {
            return true;
        }

        if (recursive(curr->next) == false) {
            return false;
        }

        if (curr->val != from_left->val) {
            return false;
        }

        from_left = from_left->next;
        return true;
    }
public:
    bool isPalindrome(ListNode* head) {
        from_left = head;

        return recursive(head);
    }
};