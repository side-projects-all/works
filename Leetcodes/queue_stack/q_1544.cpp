/*
Given a string s of lower and upper case English letters.

A good string is a string which doesn't have two adjacent characters s[i] and s[i + 1] where:

    0 <= i <= s.length - 2
    s[i] is a lower-case letter and s[i + 1] is the same letter but in upper-case or vice-versa.

To make the string good, you can choose two adjacent characters that make the string bad and remove them. You can keep doing this until the string becomes good.

Return the string after making it good. The answer is guaranteed to be unique under the given constraints.

Notice that an empty string is also good.

 

Example 1:

Input: s = "leEeetcode"
Output: "leetcode"
Explanation: In the first step, either you choose i = 1 or i = 2, both will result "leEeetcode" to be reduced to "leetcode".

Example 2:

Input: s = "abBAcC"
Output: ""
Explanation: We have many possible scenarios, and all lead to the same answer. For example:
"abBAcC" --> "aAcC" --> "cC" --> ""
"abBAcC" --> "abBA" --> "aA" --> ""

Example 3:

Input: s = "s"
Output: "s"

 

Constraints:

    1 <= s.length <= 100
    s contains only lower and upper case English letters.


*/

class Solution {
    std::string byTwoPointer(std::string& s) {
        std::size_t end = 0;

        for (std::size_t curr = 0; curr < s.size(); ++curr) {
            if (end > 0 && std::abs(s[curr] - s[end - 1]) == 32) {
                --end;
            } else {
                //it is similar to using the string s be an in place stack, 
                //making the end index as the top of the stack, and add a letter if 
                //it were not the bad part of the string s
                s[end] = s[curr];
                ++end;
            }
        }
        return s.substr(0, end);
    }
    std::string byStack(std::string& s) {
        std::string ans;
        ans.push_back(s[0]);

        for (std::size_t i = 1; i < s.size(); ++i) {
            if (ans.size() > 0 && std::abs(s[i] - ans.back()) == 32) {
                ans.pop_back();
            } else {
                ans.push_back(s[i]);
            }
        }

        return ans;
    }
public:
    string makeGood(string s) {
        //return byStack(s);
        return byTwoPointer(s);
    }
};