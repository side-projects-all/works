/*
Given the head of a linked list, return the list after sorting it in ascending order.

 

Example 1:

Input: head = [4,2,1,3]
Output: [1,2,3,4]

Example 2:

Input: head = [-1,5,3,4,0]
Output: [-1,0,3,4,5]

Example 3:

Input: head = []
Output: []

 

Constraints:

    The number of nodes in the list is in the range [0, 5 * 10^4].
    -10^5 <= Node.val <= 10^5

 

Follow up: Can you sort the linked list in O(n logn) time and O(1) memory (i.e. constant space)?

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
    ListNode* find_mid(ListNode* fast) {
        ListNode* slow = fast;
        //need this node to stop before mid and cut the link to next off
        ListNode* prev = nullptr;   

        while (fast != nullptr && fast->next != nullptr) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* mid = slow;
        prev->next = nullptr;

        return mid;
    }
    ListNode* merge(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode(-1);
        ListNode* now = dummy;

        while (list1 && list2) {
            if (list1->val < list2->val) {
                now->next = list1;
                list1 = list1->next;
            } else {
                now->next = list2;
                list2 = list2->next;
            }

            now = now->next;
        }

        if (list1)
            now->next = list1;
        else
            now->next = list2;

        return dummy->next;
    }
    ListNode* byMerge(ListNode* head) {
        //corner case: empty or 1 node
        if (!head || !head->next) {
            return head;
        }

        ListNode* mid = find_mid(head);
        ListNode* left = byMerge(head);
        ListNode* right = byMerge(mid);

        return merge(left, right);
    }

    ListNode* byPQ(ListNode* head) {
        ListNode* now = head;
        if (now == nullptr) {
            return now;
        }

        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

        while (now != nullptr) {
            pq.push(now->val);
            now = now->next;
        }

        head = new ListNode(0);
        head->next = new ListNode(pq.top());
        pq.pop();
        now = head->next;

        while (!pq.empty()) {
            now->next = new ListNode(pq.top());
            pq.pop();
            now = now->next;
        }

        return head->next;
    }
public:
    ListNode* sortList(ListNode* head) {
        //return byPQ(head);
        return byMerge(head);
    }
};
