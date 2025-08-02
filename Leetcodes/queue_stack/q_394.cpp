/*
Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there will not be input like 3a or 2[4].

The test cases are generated so that the length of the output will never exceed 105.

 

Example 1:

Input: s = "3[a]2[bc]"
Output: "aaabcbc"

Example 2:

Input: s = "3[a2[c]]"
Output: "accaccacc"

Example 3:

Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"

 

Constraints:

    1 <= s.length <= 30
    s consists of lowercase English letters, digits, and square brackets '[]'.
    s is guaranteed to be a valid input.
    All the integers in s are in the range [1, 300].


*/


class Solution {
public:
    string decodeString(string s) {
        int n = s.size();
        std::stack<std::string> str_stack;
        std::stack<int> cnt_stack;
        int cnt = 0;
        std::string curr_str;

        for (int i = 0; i < n; ++i) {

            if (std::isdigit(s[i])) {
                cnt = cnt * 10 + s[i] - '0';

            } else if (s[i] == '[') {
                cnt_stack.push(cnt);
                str_stack.push(curr_str);
                curr_str.clear();
                cnt = 0;

            } else if (s[i] == ']') {
                std::string decode = str_stack.top();
                str_stack.pop();

                int total = cnt_stack.top();
                cnt_stack.pop();
                for (int j = 0; j < total; ++j) {
                    decode += curr_str;
                }

                curr_str = std::move(decode);

            } else {
                curr_str.push_back(s[i]);
            }
        }

        return curr_str;
    }
};