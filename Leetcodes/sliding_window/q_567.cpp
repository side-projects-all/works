/*
Given two strings s1 and s2, return true if s2 contains a
permutation
of s1, or false otherwise.

In other words, return true if one of s1's permutations is the substring of s2.

 

Example 1:

Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").

Example 2:

Input: s1 = "ab", s2 = "eidboaoo"
Output: false

 

Constraints:

    1 <= s1.length, s2.length <= 10^4
    s1 and s2 consist of lowercase English letters.


*/

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n1 = s1.size();
        int n2 = s2.size();

        if (n1 > n2) {
            return false;
        }
        std::vector<int> chars(26);

        for (int i = 0; i < n1; ++i) {
            chars[s1[i] - 'a'] += 1;
        }

        for (int i = 0; i < n2; ++i) {
            chars[s2[i] - 'a'] -= 1;

            if (i - n1 >= 0) {
                chars[s2[i - n1] - 'a'] += 1;
            }

            if (all_zero(chars)) {
                return true;
            }
        }

        return false;
    }

private:
    bool all_zero(std::vector<int>& arr) {
        for (int j = 0; j < 26; ++j) {
            if (arr[j] != 0) {
                return false;
            }
        }

        return true;
    }
};