/*
Given two strings s and goal, return true if and only if s can become goal after some number of shifts on s.

A shift on s consists of moving the leftmost character of s to the rightmost position.

    For example, if s = "abcde", then it will be "bcdea" after one shift.

 

Example 1:

Input: s = "abcde", goal = "cdeab"
Output: true

Example 2:

Input: s = "abcde", goal = "abced"
Output: false

 

Constraints:

    1 <= s.length, goal.length <= 100
    s and goal consist of lowercase English letters.


*/

class Solution {
public:
    bool rotateString(string s, string goal) {
        int n = s.size();
        int m = goal.size();
        if (n != m) {
            return false;
        }

        if (n == 1 && m == 1) {
            return s[0] == goal[0];
        }

        std::string s2 = s + s;

        return s2.find(goal) < s2.size();
    }
};