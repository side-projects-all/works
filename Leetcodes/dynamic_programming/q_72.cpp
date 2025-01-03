/*
Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

You have the following three operations permitted on a word:

    Insert a character
    Delete a character
    Replace a character

 

Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')

Example 2:

Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')

 

Constraints:

    0 <= word1.length, word2.length <= 500
    word1 and word2 consist of lowercase English letters.


*/

class Solution {
private:
    int iterative(string& w1, string& w2) {
        int len1 = w1.size();
        int len2 = w2.size();

        if (len1 == 0) {
            return len2;
        }
        
        if (len2 == 0) {
            return len1;
        }
        
        std::vector<std::vector<int>> mem(len1 + 1, std::vector<int>(len2 + 1, 0));

        for (int i1 = 1; i1 <= len1; ++i1) {
            mem[i1][0] = i1;
        }

        for (int i2 = 1; i2 <= len2; ++i2) {
            mem[0][i2] = i2;
        }

        for (int i1 = 1; i1 <= len1; ++i1) {
            for (int i2 = 1; i2 <= len2; ++i2) {
            
                if (w1[i1 - 1] == w2[i2 - 1]) {
                    mem[i1][i2] = mem[i1 - 1][i2 - 1];
                } else {
                    int del = mem[i1 - 1][i2];
                    int ins = mem[i1][i2 - 1];
                    int rep = mem[i1 - 1][i2 - 1];

                    mem[i1][i2] = 1 + std::min(del, std::min(ins, rep));
                }
            }
        }

        return mem[len1][len2];
    }

    int recursive(string& w1, string& w2) {
        int len1 = w1.size();
        int len2 = w2.size();
        std::vector<std::vector<int>> mem(len1 + 1, std::vector<int>(len2 + 1, -1));

        std::function<int(int, int)> recurr = [&](int i1, int i2) -> int {
            if (i1 == 0) {
                return i2;
            }

            if (i2 == 0) {
                return i1;
            }

            if (mem[i1][i2] != -1) {
                return mem[i1][i2];
            }

            int minDis = 0;
            if (w1[i1 - 1] == w2[i2 - 1]) {
                return recurr(i1 - 1, i2 - 1);
            } else {
                int del = recurr(i1 - 1, i2);
                int ins = recurr(i1, i2 - 1);
                int rep = recurr(i1 - 1, i2 - 1);

                minDis = 1 + std::min(del, std::min(ins, rep));
            }

            return mem[i1][i2] = minDis;
        };

        return recurr(len1, len2);
    }
public:
    int minDistance(string word1, string word2) {
        //return recursive(word1, word2);
        return iterative(word1, word2);
    }
};