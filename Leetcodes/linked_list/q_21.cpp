/* 
You are given the heads of two sorted linked lists list1 and list2.

Merge the two lists in a one sorted list. The list should be made by splicing together the nodes of the first two lists.

Return the head of the merged linked list.

 

Example 1:

Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]

Example 2:

Input: list1 = [], list2 = []
Output: []

Example 3:

Input: list1 = [], list2 = [0]
Output: [0]

 

Constraints:

    The number of nodes in both lists is in the range [0, 50].
    -100 <= Node.val <= 100
    Both list1 and list2 are sorted in non-decreasing order.


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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        //return old(list1, list2);
        //return recursive(list1, list2);
        return iterative(list1, list2);
    }

private:
    ListNode* iterative(ListNode* now1, ListNode* now2) {
        ListNode* preHead = new ListNode(-1);
        ListNode* prev = preHead;

        while (now1 != nullptr && now2 != nullptr) {
            if (now1->val > now2->val) {
                prev->next = now2;
                now2 = now2->next;
            } else {
                prev->next = now1;
                now1 = now1->next;
            }

            prev = prev->next;
        }

        prev->next = (now1 == nullptr ? now2 : now1);
        return preHead->next;
        /*
        ListNode* newHead = nullptr;
        ListNode* last = nullptr;

        if (now1 == nullptr) {
            return now2;
        } else if (now2 == nullptr) {
            return now1;
        }

        std::function<void(ListNode*&, ListNode*&, ListNode*&)> changeConn = [&](ListNode* &list,  ListNode* &h, ListNode* &e) {
            if (e == nullptr) {
                h = list;
                e = h;

                list = list->next;
                e->next = nullptr;
            } else {
                e->next = list;
                e = e->next;

                list = list->next;
                e->next = nullptr;
            }
        };

        while (now1 != nullptr || now2 != nullptr) {
            if (now1 == nullptr) {
                changeConn(now2, newHead, last);

            } else if (now2 == nullptr) {
                changeConn(now1, newHead, last);

            } else if (now1->val > now2->val) {
                changeConn(now2, newHead, last);

            } else {
                //for scenario: now1->val <= now2->val
                changeConn(now1, newHead, last);
            }
        }

        return newHead;
        */
    }
    ListNode* recursive(ListNode* now1, ListNode* now2) {
        if (now1 == NULL && now2 == NULL) {
            return now1;
        } else if (now1 == NULL && now2 != NULL) {
            return now2;
        } else if (now1 != NULL && now2 == NULL) {
            return now1;
        } 

        ListNode* tmp = NULL;
        if (now1->val > now2->val) {
            tmp = now2->next;
            now2->next = recursive(now1, tmp);
            return now2;

        } else {
            tmp = now1->next;
            now1->next = recursive(tmp, now2);
            return now1;
        }
    }

    ListNode* old(ListNode* list1, ListNode* list2) {
        if (list1 == NULL) {
            return list2;
            
        } else if (list2 == NULL) {
            return list1;
            
        } else if (list1->val < list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        } else {
            list2->next = mergeTwoLists(list1, list2->next);
            return list2;
        }
    }
};