/*
A critical point in a linked list is defined as either a local maxima or a local minima.

A node is a local maxima if the current node has a value strictly greater than the previous node and the next node.

A node is a local minima if the current node has a value strictly smaller than the previous node and the next node.

Note that a node can only be a local maxima/minima if there exists both a previous node and a next node.

Given a linked list head, return an array of length 2 containing [minDistance, maxDistance] where minDistance is the minimum distance between any two distinct critical points and maxDistance is the maximum distance between any two distinct critical points. If there are fewer than two critical points, return [-1, -1].

 

Example 1:

Input: head = [3,1]
Output: [-1,-1]
Explanation: There are no critical points in [3,1].

Example 2:

Input: head = [5,3,1,2,5,1,2]
Output: [1,3]
Explanation: There are three critical points:
- [5,3,1,2,5,1,2]: The third node is a local minima because 1 is less than 3 and 2.
- [5,3,1,2,5,1,2]: The fifth node is a local maxima because 5 is greater than 2 and 1.
- [5,3,1,2,5,1,2]: The sixth node is a local minima because 1 is less than 5 and 2.
The minimum distance is between the fifth and the sixth node. minDistance = 6 - 5 = 1.
The maximum distance is between the third and the sixth node. maxDistance = 6 - 3 = 3.

Example 3:

Input: head = [1,3,2,2,3,2,2,2,7]
Output: [3,3]
Explanation: There are two critical points:
- [1,3,2,2,3,2,2,2,7]: The second node is a local maxima because 3 is greater than 1 and 2.
- [1,3,2,2,3,2,2,2,7]: The fifth node is a local maxima because 3 is greater than 2 and 2.
Both the minimum and maximum distances are between the second and the fifth node.
Thus, minDistance and maxDistance is 5 - 2 = 3.
Note that the last node is not considered a local maxima because it does not have a next node.

 

Constraints:

    The number of nodes in the list is in the range [2, 10^5].
    1 <= Node.val <= 10^5


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
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
            return {-1, -1};
        }

        ListNode* pre = head;
        ListNode* now = pre->next;

        //without vector
        //std::vector<int> positions;
        int i_now = 1;
        int i_pre = 0;
        int i_min = 1;
        int min_dis = INT_MAX;
        while (now != nullptr && now->next != nullptr) {

            if ((pre->val < now->val && now->val > now->next->val) || 
                    (pre->val > now->val && now->val < now->next->val)) {

                //positions.push_back(i);
                if (i_pre == 0) {
                    i_min = i_now;
                    i_pre = i_now;
                } else {
                    min_dis = std::min(min_dis, i_now - i_pre);
                    i_pre = i_now;
                }
            }
            pre = now;
            now = now->next;
            ++i_now;
            //++i;
        }

        std::vector<int> ans{ -1, -1 };
        if (min_dis == INT_MAX) {
            return ans;
        }

        ans[0] = min_dis;
        ans[1] = i_pre - i_min;
        /*
        if (positions.size() < 2) {
            return ans;
        }

        int min = INT_MAX;
        for (int i = 1; i < positions.size(); ++i) {
            min = std::min(min, positions[i] - positions[i - 1]);
        }

        ans[0] = min;
        ans[1] = positions[positions.size() - 1] - positions[0];
        */

        return ans;
    }
};