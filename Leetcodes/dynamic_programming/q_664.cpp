/*
There is a strange printer with the following two special properties:

    The printer can only print a sequence of the same character each time.
    At each turn, the printer can print new characters starting from and ending at any place and will cover the original existing characters.

Given a string s, return the minimum number of turns the printer needed to print it.

 

Example 1:

Input: s = "aaabbb"
Output: 2
Explanation: Print "aaa" first and then print "bbb".

Example 2:

Input: s = "aba"
Output: 2
Explanation: Print "aaa" first and then print "b" from the second place of the string, which will cover the existing character 'a'.

 

Constraints:

    1 <= s.length <= 100
    s consists of lowercase English letters.


*/

class Solution {
private:
    int recursive(string& s, int left, int right, std::vector<std::vector<int>>& mem) {

        if (mem[left][right] != -1) {
            return mem[left][right];
        }

        mem[left][right] = s.size();
        int j = -1;
        for (int i = left; i < right; ++i) {
            //find first s[i] that is not equal to s[right]!!
            if (s[i] != s[right] && j == -1) {
                j = i;
            }

            //because of i is moving, we separate them into two parts!!
            if (j != -1) {
                mem[left][right] = std::min(mem[left][right], 
                                        1 + recursive(s, j, i, mem) + recursive(s, i + 1, right, mem));
            }
        }

        if (j == -1) {
             mem[left][right] = 0;
        }

        return mem[left][right];
    }
public:
    int strangePrinter(string s) {
        std::vector<std::vector<int>> mem(s.size(), std::vector<int>(s.size(), -1));

        return 1 + recursive(s, 0, s.size() - 1, mem);
    }
};