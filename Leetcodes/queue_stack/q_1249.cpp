/*
Given a string s of '(' , ')' and lowercase English characters.

Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so that the resulting parentheses string is valid and return any valid string.

Formally, a parentheses string is valid if and only if:

    It is the empty string, contains only lowercase characters, or
    It can be written as AB (A concatenated with B), where A and B are valid strings, or
    It can be written as (A), where A is a valid string.

 

Example 1:

Input: s = "lee(t(c)o)de)"
Output: "lee(t(c)o)de"
Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.

Example 2:

Input: s = "a)b(c)d"
Output: "ab(c)d"

Example 3:

Input: s = "))(("
Output: ""
Explanation: An empty string is also valid.

 

Constraints:

    1 <= s.length <= 10^5
    s[i] is either'(' , ')', or lowercase English letter.


*/

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        std::unordered_set<int> toRemove;
        std::deque<int> left_p;

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                left_p.push_back(i);

            } else if (s[i] == ')') {
                if (left_p.empty()) {
                    toRemove.insert(i);
                } else {
                    left_p.pop_back();
                }

            }
        }

        while (!left_p.empty()) {
            toRemove.insert(left_p.back());
            left_p.pop_back();
        }

        std::string ans;
        for (int i = 0; i < s.size(); ++i) {
            
            if (toRemove.find(i) == toRemove.end()) {
                ans.push_back(s[i]);
            }
        }

        return ans;
    }
};