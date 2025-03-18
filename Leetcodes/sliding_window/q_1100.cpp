/*
Given a string s and an integer k, return the number of substrings in s of length k with no repeated characters.

 

Example 1:

Input: s = "havefunonleetcode", k = 5
Output: 6
Explanation: There are 6 substrings they are: 'havef','avefu','vefun','efuno','etcod','tcode'.

Example 2:

Input: s = "home", k = 5
Output: 0
Explanation: Notice k can be larger than the length of s. In this case, it is not possible to find any substring.

 

Constraints:

    1 <= s.length <= 10^4
    s consists of lowercase English letters.
    1 <= k <= 10^4


*/

class Solution {
public:
    int numKLenSubstrNoRepeats(string s, int k) {
        int n = s.size();
        int b = 0;
        int e = 0;

        int cnt = 0;
        std::vector<int> cnts(26);
        while (e < n) {
            ++cnts[s[e] - 'a'];

            while (cnts[s[e] - 'a'] > 1 || e - b + 1 > k) {

                if (cnts[s[b] - 'a'] > 0) {
                    --cnts[s[b] - 'a'];
                }

                ++b;
            }

            if (e - b + 1 == k) {
                ++cnt;
            }
            ++e;
        }

        return cnt;
    }
};