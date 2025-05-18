/*
You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.

 

Example 1:

Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6

Example 2:

Input: lists = []
Output: []

Example 3:

Input: lists = [[]]
Output: []

 

Constraints:

    k == lists.length
    0 <= k <= 10^4
    0 <= lists[i].length <= 500
    -10^4 <= lists[i][j] <= 10^4
    lists[i] is sorted in ascending order.
    The sum of lists[i].length will not exceed 10^4.


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
    ListNode* merge_2_lists(ListNode* list1, ListNode* list2) {
        ListNode* l1 = list1;
        ListNode* l2 = list2;
        ListNode* dummy = new ListNode();
        ListNode* b = dummy;

        while (l1 != nullptr && l2 != nullptr) {

            if (l1->val <= l2->val) {
                b->next = l1;
                l1 = l1->next;

            } else {
                b->next = l2;
                l2 = l2->next;
            }

            b = b->next;
        }

        if (l1 != nullptr) {
            b->next = l1;
        } else {
            b->next = l2;
        }

        return dummy->next;
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        if (n == 0) {
            return nullptr;
        }
        if (n == 1) {
            return lists[0];
        }

        int interval = 1;

        while (interval < n) {

            for (int i = 0; i < n; i += interval * 2) {

                if (i + interval < n) {
                    lists[i] = merge_2_lists(lists[i], lists[i + interval]);
                }
            }

            interval *= 2;
        }
        
        return lists[0];
    }
};