/*
Given a string s containing only three types of characters: '(', ')' and '*', return true if s is valid.

The following rules define a valid string:

    Any left parenthesis '(' must have a corresponding right parenthesis ')'.
    Any right parenthesis ')' must have a corresponding left parenthesis '('.
    Left parenthesis '(' must go before the corresponding right parenthesis ')'.
    '*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string "".

 

Example 1:

Input: s = "()"
Output: true

Example 2:

Input: s = "(*)"
Output: true

Example 3:

Input: s = "(*))"
Output: true

 

Constraints:

    1 <= s.length <= 100
    s[i] is '(', ')' or '*'.


*/

class Solution {
private:
    bool byTwoPointers(string& s) {
        int left_parenthesis = 0;
        int right_parenthesis = 0;
        int N = s.size();

        for (int i = 0; i < N; ++i) {
            if (s[i] == '(' || s[i] == '*') {
                ++left_parenthesis;
            } else {
                --left_parenthesis;
            }

            if (s[N - i - 1] == ')' || s[N - i - 1] == '*') {
                ++right_parenthesis;
            } else {
                --right_parenthesis;
            }

            if (left_parenthesis < 0 || right_parenthesis < 0) {
                return false;
            }
        }

        return true;
    }
    bool byTwoStacks(string& s) {
        std::stack<int> stackP;
        std::stack<int> stackS;

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] =='(') {
                stackP.push(i);

            } else if (s[i] ==')') {

                if (!stackP.empty()) {
                    stackP.pop();
                } else if (!stackS.empty()) {
                    stackS.pop();
                } else {
                    return false;
                }
                
            } else {
                stackS.push(i);
            }
        }

        while (!stackP.empty() && !stackS.empty()) {
            if (stackP.top() > stackS.top()) {
                return false;
            }

            stackP.pop();
            stackS.pop();
        }

        return stackP.empty();
    }
public:
    bool checkValidString(string s) {
        //return byTwoStacks(s);
        return byTwoPointers(s);
    }
};