/*
Write a function that reverses a string. The input string is given as an array of characters s.

You must do this by modifying the input array in-place with O(1) extra memory.

 

Example 1:

Input: s = ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]

Example 2:

Input: s = ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]

 

Constraints:

    1 <= s.length <= 10^5
    s[i] is a printable ascii character.


*/

class Solution {
public:
    void reverseString(vector<char>& s) {
        if (s.size() == 1) {
            return;
        }

        int b = 0;
        int e = s.size() - 1;
        while (b < e) {
            char tmp = s[b];
            s[b] = s[e];
            s[e] = tmp;
            
            ++b;
            --e;
        }
    }
};