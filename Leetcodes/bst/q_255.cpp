/*
Given an array of unique integers preorder, return true if it is the correct preorder traversal sequence of a binary search tree.

 

Example 1:

Input: preorder = [5,2,1,3,6]
Output: true

Example 2:

Input: preorder = [5,2,6,1,3]
Output: false

 

Constraints:

    1 <= preorder.length <= 104
    1 <= preorder[i] <= 104
    All the elements of preorder are unique.

*/

class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        int minLimit = -1;
        std::stack<int> s;

        for (int num : preorder) {
            while (!s.empty() && s.top() < num) {
                minLimit = s.top();
                s.pop();
            }

            if (num <= minLimit) {
                return false;
            }

            s.push(num);
        }

        return true;
    }
};