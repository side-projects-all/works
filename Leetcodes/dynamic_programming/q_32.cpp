/*
Given a string containing just the characters '(' and ')', return the length of the longest valid (well-formed) parentheses
substring
.

 

Example 1:

Input: s = "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()".

Example 2:

Input: s = ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()".

Example 3:

Input: s = ""
Output: 0

 

Constraints:

    0 <= s.length <= 3 * 10^4
    s[i] is '(', or ')'.


*/

class Solution {
    int iterative(std::string& s) {
        //record how many valid parentheses at the current index
        std::vector<int> mem(s.size(), 0);

        int max = 0;
        for (int i = 1; i < s.size(); ++i) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') {
                    mem[i] = (i >= 2 ? mem[i - 2] : 0) + 2;

                } else if (i - mem[i - 1] > 0 && s[i - mem[i - 1] - 1] == '(') {
                    mem[i] = mem[i - 1] + ((i - mem[i - 1]) >= 2 ? mem[i - mem[i - 1] - 2] : 0) + 2;
                }

                max = std::max(max, mem[i]);
            }
        }

        return max;
    }
    int byStack(std::string& s) {
        int max = 0;

        std::stack<int> stack;
        stack.push(-1);
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                stack.push(i);
            } else {

                stack.pop();

                if (stack.empty()) {
                    stack.push(i);
                } else {
                    max = std::max(max, i - stack.top());
                }
            }
        }

        return max;
    }
public:
    int longestValidParentheses(string s) {
        //return byStack(s);
        return iterative(s);
    }
};