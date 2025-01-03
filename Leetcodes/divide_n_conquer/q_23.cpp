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
    ListNode* byMerge(vector<ListNode*>& lists) {
        int N = lists.size();

        if (N == 0) {
            return nullptr;
        }

        int interval = 1;

        std::function<ListNode*(ListNode*, ListNode*)> mergeTwoList = [&](ListNode* h1, ListNode* h2) -> ListNode* {
            ListNode* head = new ListNode();
            ListNode* ptr = head;

            while (h1 != nullptr && h2 != nullptr) {

                if (h1->val <= h2->val) {
                    ptr->next = h1;
                    h1 = h1->next;
                } else {
                    ptr->next = h2;
                    h2 = h1;
                    h1 = ptr->next->next;
                }

                ptr = ptr->next;
            }

            if (h1 == nullptr) {
                ptr->next = h2;
            } else {
                ptr->next = h1;
            }

            return head->next;
        };

        while (interval < N) {
            for (int i = 0; i < N - interval; i += interval * 2) {
                lists[i] = mergeTwoList(lists[i], lists[i + interval]);
            }

            interval *= 2;
        }

        return lists[0];
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return byMerge(lists);
    }
};