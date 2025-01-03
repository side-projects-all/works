/*
Given a character array s, reverse the order of the words.

A word is defined as a sequence of non-space characters. The words in s will be separated by a single space.

Your code must solve the problem in-place, i.e. without allocating extra space.

 

Example 1:

Input: s = ["t","h","e"," ","s","k","y"," ","i","s"," ","b","l","u","e"]
Output: ["b","l","u","e"," ","i","s"," ","s","k","y"," ","t","h","e"]

Example 2:

Input: s = ["a"]
Output: ["a"]

 

Constraints:

    1 <= s.length <= 10^5
    s[i] is an English letter (uppercase or lowercase), digit, or space ' '.
    There is at least one word in s.
    s does not contain leading or trailing spaces.
    All the words in s are guaranteed to be separated by a single space.


*/

class Solution {
public:
    void reverseWords(vector<char>& s) {
        if (s.size() == 1) {
            return;
        }

        int left = 0;
        int right = s.size() - 1;

        while (left < right) {
            char tmp = s[left];
            s[left] = s[right];
            s[right] = tmp;

            ++left;
            --right;
        }

        left = 0;
        right = 0;
        int i = 0;
        while (i < s.size()) {
            //find space
            while (right < s.size() && s[right] != ' ') {
                ++right;
            }

            i = right + 1;
            right -= 1;
            //then exchange left right
            while (left < right) {
                char tmp = s[left];
                s[left] = s[right];
                s[right] = tmp;

                ++left;
                --right;
            }

            left = i;
            right = i;
        }

    }
};