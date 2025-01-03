/*
Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, '+', '-', '*', '/' operators, and open '(' and closing parentheses ')'. The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

Example 1:

Input: s = "1+1"
Output: 2

Example 2:

Input: s = "6-4/2"
Output: 4

Example 3:

Input: s = "2*(5+5*2)/3+(6/2+8)"
Output: 21

 

Constraints:

    1 <= s <= 10^4
    s consists of digits, '+', '-', '*', '/', '(', and ')'.
    s is a valid expression.


*/

class Solution {
private:
    void evaluate(char op, std::string& first, std::string& second, std::string& result) {
        int x = std::stoi(first);
        int y = std::stoi(second);
        int res = 0;

        if (op == '+') {
            res = x;
        } else if (op == '-') {
            res = -x;
        } else if (op == '*') {
            res = x * y;
        } else {
            res = x / y;
        }

        result += std::to_string(res);
    }
public:
    int calculate(string s) {
        /*
        std::stack<std::string> stack;
        std::string curr = "";
        char prevOp = '+';  //important
        s += "@";
        std::unordered_set<std::string> ops = { "+", "-", "*", "/" };

        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];

            if (std::isdigit(c)) {
                curr += c;

            } else if (c == '(') {
                stack.push(std::string(1, prevOp));

                prevOp = '+';
            } else {

                if (prevOp == '*' || prevOp == '/') {
                    std::string result = "";
                    std::string first = stack.top();
                    stack.pop();

                    evaluate(prevOp, first, curr, result);

                    stack.push(result);

                } else {

                    std::string result = "";
                    std::string second = "0";

                    evaluate(prevOp, curr, second, result);

                    stack.push(result);
                }

                curr = "";
                prevOp = c;

                if (c == ')') {
                    int currTerm = 0;

                    while (ops.find(stack.top()) == ops.end()) {
                        currTerm += std::stoi(stack.top());
                        stack.pop();
                    }

                    curr = std::to_string(currTerm);
                    prevOp = stack.top()[0];
                    stack.pop();
                }
            }
        }

        int ans = 0;
        while (!stack.empty()) {
            std::string s = stack.top();
            stack.pop();

            ans += std::stoi(s);
        }

        return ans;
        */

        //fantastic Solution
        int ret = 0;
        int prev = 0;
        int num = 0;
        int oper = '+';
        stack<int> rets;
        stack<int> prevs;
        stack<char> opers;

        for (int i = 0; i < s.length(); i++) {
            if (std::isdigit(s[i])) {
                num = num * 10 + s[i] - '0';

            } else if (s[i] == '(') {
                rets.push(ret);
                ret = 0;
                prevs.push(prev);
                prev = 0;
                opers.push(oper);
                oper = '+';

            } else if (s[i] == ')') {
                if (oper == '*') prev *= num;
                else if (oper == '/') prev /= num;
                else prev = (oper == '-' ? (-1) * num : num);

                num = ret + prev;

                if (!rets.empty()) {
                    ret = rets.top();
                    rets.pop();
                    prev = prevs.top();
                    prevs.pop();
                    oper = opers.top();
                    opers.pop();
                }
            }

            if ( (!std::isdigit(s[i]) && s[i] != '(' && s[i] != ')') ||
                                                            i == s.length() - 1 ) {
                if (oper == '*') prev *= num;
                else if (oper == '/') prev = prev / num;
                else prev = (oper == '-' ? (-1) * num : num);

                if (s[i] == '+' || s[i] == '-') {
                    ret += prev;
                    prev = 0;
                }
                
                num = 0;
                oper = s[i];
            }
            
        }

        return ret + prev;
    }
};