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
        std::unordered_map<char, char> characters = { {'(', ')'}, 
                                                      {'{', '}'}, 
                                                      {'[', ']'},
                                                      {')', ')'}, 
                                                      {'}', '}'}, 
                                                      {']', ']'} };
        
        std::vector<char> stack;
        char key;
        for (int i = s.length() - 1; i > -1 ; --i) {
            
            key = s[i];
            //return if wrong character
            if (characters.find(key) == characters.end()) {
                return false;
            }
            //not need to compare if empty stack
            if (stack.size() == 0) {
                stack.push_back(s[i]);
                continue;
            }
            //check with last element
            if (stack.back() == characters[key] && stack.back() != key) {
                stack.pop_back();
            } else {
                stack.push_back(s[i]);
            }
        }
        
        if (stack.empty()) {
            return true;
        }
            
        return false;
    }
};