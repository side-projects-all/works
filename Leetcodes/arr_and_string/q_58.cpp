/*
Given a string s consisting of words and spaces, return the length of the last word in the string.

A word is a maximal
substring
consisting of non-space characters only.

 

Example 1:

Input: s = "Hello World"
Output: 5
Explanation: The last word is "World" with length 5.

Example 2:

Input: s = "   fly me   to   the moon  "
Output: 4
Explanation: The last word is "moon" with length 4.

Example 3:

Input: s = "luffy is still joyboy"
Output: 6
Explanation: The last word is "joyboy" with length 6.

 

Constraints:

    1 <= s.length <= 10^4
    s consists of only English letters and spaces ' '.
    There will be at least one word in s.


*/

class Solution {
public:
    int lengthOfLastWord(string s) {

        //from the end to meet first non-space character
        int i = 0;
        for (i = s.size() - 1; i > -1; --i) {
            if (s[i] != ' ') {
                break;
            }
        }

        int cnt = 0;
        for (i = i; i > -1; --i) {
            if (s[i] != ' ') {
                ++cnt;
            } else {
                break;
            }
        }

        return cnt;
    }
};