/*
Given a string s, return the number of substrings that have only one distinct letter.

 

Example 1:

Input: s = "aaaba"
Output: 8
Explanation: The substrings with one distinct letter are "aaa", "aa", "a", "b".
"aaa" occurs 1 time.
"aa" occurs 2 times.
"a" occurs 4 times.
"b" occurs 1 time.
So the answer is 1 + 2 + 4 + 1 = 8.

Example 2:

Input: s = "aaaaaaaaaa"
Output: 55

 

Constraints:

    1 <= s.length <= 1000
    s[i] consists of only lowercase English letters.


*/

class Solution {
public:
    int countLetters(string s) {

        int cnt = 0;
        for (int i = 0; i < s.size(); ++i) {

            int start = i;
            int end = i + 1;
            while (end < s.size() && s[end] == s[end - 1]) {
                ++end;
            }

            int sum = (1 + (end - start)) * (end - start) / 2;
            cnt += sum;

            i = end - 1;
        }

        return cnt;
    }
};