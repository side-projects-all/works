/*
Given a string s which represents an expression, evaluate this expression and return its value. 

The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

Example 1:

Input: s = "3+2*2"
Output: 7

Example 2:

Input: s = " 3/2 "
Output: 1

Example 3:

Input: s = " 3+5 / 2 "
Output: 5

 

Constraints:

    1 <= s.length <= 3 * 105
    s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
    s represents a valid expression.
    All the integers in the expression are non-negative integers in the range [0, 231 - 1].
    The answer is guaranteed to fit in a 32-bit integer.


*/

class Solution {
public:
    int calculate(string s) {
        int N = s.size();

        int currNum = 0;
        char operation = '+';   //this is important! for first operation
        std::stack<int> stack;

        for (int i = 0; i < N; ++i) {
            char c = s[i];

            if (std::isdigit(c)) {
                currNum = (currNum * 10) + (c - '0');
            }

            if ((!std::isdigit(c) && !std::iswspace(c)) || i == N -1) {
                
                if (operation == '-') {
                    stack.push(-currNum);

                } else if (operation == '+') {
                    stack.push(currNum);

                } else if (operation == '*') {
                    int val = stack.top();
                    stack.pop();
                    stack.push(val * currNum);
                    
                } else if (operation == '/') {
                    int val = stack.top();
                    stack.pop();
                    stack.push(val / currNum);
                }

                operation = c;
                currNum = 0;
            }

        }

        int result = 0;
        while (!stack.empty()) {
            result += stack.top();
            stack.pop();
        }

        return result;
    }
};