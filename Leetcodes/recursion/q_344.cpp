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

    1 <= s.length <= 105
    s[i] is a printable ascii character.


*/

class Solution {
public:
    void reverseString(vector<char>& s) {
        /*
        char replace = s[(s.size() - (pos + 1))];
        if (pos != (s.size() - 1)) {
            ++pos;
            reverseString(s);
        }

        s[pos] = replace;
        --pos;
        */

        recursion(0, s.size() - 1, s);
        //byLoop(0, s.size() - 1, s);
    }
private:
    //int pos = 0;

    void recursion(int s, int e, std::vector<char>& str) {
        if (s >= e) {
            return;
        }

        char tmp = str[s];
        str[s] = str[e];
        str[e] = tmp;

        return recursion(s + 1, e - 1, str);
    }

    void byLoop(int s, int e, std::vector<char>& str) {

        char tmp = str[s]; 
        while(s < e) {
            tmp = str[s];
            str[s++] = str[e];
            str[e--] = tmp;
        }
    }

};