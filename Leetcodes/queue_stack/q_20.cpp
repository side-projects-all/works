/*
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

    Open brackets must be closed by the same type of brackets.
    Open brackets must be closed in the correct order.
    Every close bracket has a corresponding open bracket of the same type.

 

Example 1:

Input: s = "()"
Output: true

Example 2:

Input: s = "()[]{}"
Output: true

Example 3:

Input: s = "(]"
Output: false

 

Constraints:

    1 <= s.length <= 10^4
    s consists of parentheses only '()[]{}'.


*/


class Solution {
public:
    bool isValid(string s) {
        int n = s.size();
        if (n % 2) {
            return false;
        }

        std::stack<char> stack;

        for (int i = 0; i < n; ++i) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                stack.push(s[i]);

            } else {

                if (stack.empty()) {
                    return false;
                }
                
                if ((s[i] == ')' && stack.top() != '(') || 
                    (s[i] == ']' && stack.top() != '[') || (s[i] == '}' && stack.top() != '{')) {
                    return false;
                }

                stack.pop();
            }
        }

        return stack.empty() ? true : false;
    }
};