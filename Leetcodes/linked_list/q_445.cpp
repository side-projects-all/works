/*
You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

 

Example 1:

Input: l1 = [7,2,4,3], l2 = [5,6,4]
Output: [7,8,0,7]

Example 2:

Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [8,0,7]

Example 3:

Input: l1 = [0], l2 = [0]
Output: [0]

 

Constraints:

    The number of nodes in each linked list is in the range [1, 100].
    0 <= Node.val <= 9
    It is guaranteed that the list represents a number that does not have leading zeros.

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
    //assume len of v1 is alwasy shorter or equal to v2
    ListNode* sumTwo(std::vector<int>& v1, std::vector<int>& v2) {
        int len = v1.size();

        ListNode* now = nullptr;
        ListNode* prev = nullptr;
        int carry = 0;
        int i = 0;

        for (i = 0; i < len; ++i) {
            prev = now;

            int val = v1[i] + v2[i] + carry;
            int res = val % 10;
            carry = val / 10;

            now = new ListNode(res);
            now->next = prev;
        }

        for (i = i; i < v2.size(); ++i) {
            prev = now;

            int val = v2[i] + carry;
            int res = val % 10;
            carry = val / 10;

            now = new ListNode(res);
            now->next = prev;
        }

        if (carry > 0) {
            prev = now;
            now = new ListNode(carry);
            now->next = prev;
        }

        return now;
    }
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        //using stack
        std::stack<int> s1;
        std::stack<int> s2;
        ListNode* ptr = l1;
        while (ptr != nullptr) {
            s1.push(ptr->val);
            ptr = ptr->next;
        }

        ptr = l2;
        while (ptr != nullptr) {
            s2.push(ptr->val);
            ptr = ptr->next;
        }

        int sum = 0;
        int carry = 0;
        ListNode* now = new ListNode(0);
        while (!s1.empty() || !s2.empty()) {
            if (!s1.empty()) {
                sum += s1.top();
                s1.pop();
            }

            if (!s2.empty()) {
                sum += s2.top();
                s2.pop();
            }

            now->val = sum % 10;
            carry = sum / 10;
            ListNode* newN = new ListNode(carry);
            newN->next = now;
            now = newN;
            sum = carry;
        }

        return carry == 0 ? now->next : now;

        //naive way
        /*
        std::vector<int> v1;
        std::vector<int> v2;

        ListNode* ptr = l1;
        while (ptr != nullptr) {
            v1.push_back(ptr->val);
            ptr = ptr->next;
        }

        ptr = l2;
        while (ptr != nullptr) {
            v2.push_back(ptr->val);
            ptr = ptr->next;
        }

        std::reverse(v1.begin(), v1.end());
        std::reverse(v2.begin(), v2.end());

        if (v1.size() > v2.size()) {
            return sumTwo(v2, v1);
        } else {
            return sumTwo(v1, v2);
        }
        */
    }
};