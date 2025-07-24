/*
Given a string s which consists of lowercase or uppercase letters, return the length of the longest

 that can be built with those letters.

Letters are case sensitive, for example, "Aa" is not considered a palindrome.

 

Example 1:

Input: s = "abccccdd"
Output: 7
Explanation: One longest palindrome that can be built is "dccaccd", whose length is 7.

Example 2:

Input: s = "a"
Output: 1
Explanation: The longest palindrome that can be built is "a", whose length is 1.

 

Constraints:

    1 <= s.length <= 2000
    s consists of lowercase and/or uppercase English letters only.

*/

class Solution {
private:
    int by_map(string& s) {
        int n = s.size();
        if (n == 1) {
            return 1;
        }

        std::unordered_map<char, int> cnts;
        for (char c : s) {
            ++cnts[c];
        }

        int len = 0;
        for (auto& p : cnts) {
            if (p.second % 2 == 0) {
                len += p.second;
            } else {
                len += p.second - 1;
            }
        }

        return len == n ? len : len + 1;
    }
public:
    int longestPalindrome(string s) {
        return by_map(s);
    }
};