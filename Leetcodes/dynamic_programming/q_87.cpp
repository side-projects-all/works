/*
We can scramble a string s to get a string t using the following algorithm:

    If the length of the string is 1, stop.
    If the length of the string is > 1, do the following:
        Split the string into two non-empty substrings at a random index, i.e., if the string is s, divide it to x and y where s = x + y.
        Randomly decide to swap the two substrings or to keep them in the same order. i.e., after this step, s may become s = x + y or s = y + x.
        Apply step 1 recursively on each of the two substrings x and y.

Given two strings s1 and s2 of the same length, return true if s2 is a scrambled string of s1, otherwise, return false.

 

Example 1:

Input: s1 = "great", s2 = "rgeat"
Output: true
Explanation: One possible scenario applied on s1 is:
"great" --> "gr/eat" // divide at random index.
"gr/eat" --> "gr/eat" // random decision is not to swap the two substrings and keep them in order.
"gr/eat" --> "g/r / e/at" // apply the same algorithm recursively on both substrings. divide at random index each of them.
"g/r / e/at" --> "r/g / e/at" // random decision was to swap the first substring and to keep the second substring in the same order.
"r/g / e/at" --> "r/g / e/ a/t" // again apply the algorithm recursively, divide "at" to "a/t".
"r/g / e/ a/t" --> "r/g / e/ a/t" // random decision is to keep both substrings in the same order.
The algorithm stops now, and the result string is "rgeat" which is s2.
As one possible scenario led s1 to be scrambled to s2, we return true.

Example 2:

Input: s1 = "abcde", s2 = "caebd"
Output: false

Example 3:

Input: s1 = "a", s2 = "a"
Output: true

 

Constraints:

    s1.length == s2.length
    1 <= s1.length <= 30
    s1 and s2 consist of lowercase English letters.


*/

class Solution {
private:
    bool recursive(string& s1, string& s2) {
        int n = s1.size();

        //n + 1 means the length of two strings; n means position!!
        std::vector<std::vector<std::vector<int>>> mem(n + 1, std::vector<std::vector<int>>(n, 
                                                                            std::vector<int>(n, -1)));

        std::function<bool(int, int, int)> recurr = [&](int i, int j, int len) -> bool {
            if (len == 1) {
                return mem[len][i][j] = (s1[i] == s2[j]);
            }

            if (mem[len][i][j] != -1) {
                return mem[len][i][j];
            }

            for (int cut = 1; cut < len; ++cut) {
                //not swap
                if (recurr(i, j, cut) && recurr(i + cut, j + cut, len -cut)) {
                    return mem[len][i][j] = 1;
                }
                //swap
                if (recurr(i, len + j - cut, cut) && recurr(i + cut, j, len - cut)) {
                    return mem[len][i][j] = 1;
                }
            }

            return mem[len][i][j] = 0;
        };

        return recurr(0, 0, n);
    }
    bool iterative(string& s1, string& s2) {
        int n = s1.size();

        //n + 1 means the length of two strings; n means position!!
        std::vector<std::vector<std::vector<int>>> mem(n + 1, std::vector<std::vector<int>>(n, 
                                                                            std::vector<int>(n)));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                mem[1][i][j] = s1[i] == s2[j];
            }
        }

        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i < n + 1 - len; ++i) {
                for (int j = 0; j < n + 1 - len; ++j) {

                    for (int newLen = 1; newLen < len; ++newLen) {
                        //const std::vector<int>& mem1 = mem[newLen][i];
                        //const std::vector<int>& mem2 = mem[len - newLen][i + newLen];

                        //the cases: not swap & swap
                        mem[len][i][j] |= mem[newLen][i][j] && mem[len - newLen][i + newLen][j + newLen];
                        mem[len][i][j] |= mem[newLen][i][j + len - newLen] && mem[len - newLen][i + newLen][j];
                        
                    }
                }
            }
        }

        return mem[n][0][0];
    }
public:
    bool isScramble(string s1, string s2) {
        //return iterative(s1, s2);
        return recursive(s1, s2);
    }
};