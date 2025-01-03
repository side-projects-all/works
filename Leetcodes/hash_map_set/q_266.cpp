/*
Given a string s, return true if a permutation of the string could form a
palindrome
and false otherwise.

 

Example 1:

Input: s = "code"
Output: false

Example 2:

Input: s = "aab"
Output: true

Example 3:

Input: s = "carerac"
Output: true

 

Constraints:

    1 <= s.length <= 5000
    s consists of only lowercase English letters.


*/

class Solution {
public:
    bool canPermutePalindrome(string s) {
        std::unordered_map<char, int> m;

        for (int i = 0; i < s.size(); ++i) {
            m[s[i]] += 1;
        }

        int countOdd = 0;
        for (auto& p : m) {
            if (p.second % 2 != 0) {
                ++countOdd;
            }
        }

        return (countOdd <= 1) ? true : false;
    }
};