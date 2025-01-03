/*
You are given two strings word1 and word2. Merge the strings by adding letters in alternating order, starting with word1. If a string is longer than the other, append the additional letters onto the end of the merged string.

Return the merged string.

 

Example 1:

Input: word1 = "abc", word2 = "pqr"
Output: "apbqcr"
Explanation: The merged string will be merged as so:
word1:  a   b   c
word2:    p   q   r
merged: a p b q c r

Example 2:

Input: word1 = "ab", word2 = "pqrs"
Output: "apbqrs"
Explanation: Notice that as word2 is longer, "rs" is appended to the end.
word1:  a   b 
word2:    p   q   r   s
merged: a p b q   r   s

Example 3:

Input: word1 = "abcd", word2 = "pq"
Output: "apbqcd"
Explanation: Notice that as word1 is longer, "cd" is appended to the end.
word1:  a   b   c   d
word2:    p   q 
merged: a p b q c   d

 

Constraints:

    1 <= word1.length, word2.length <= 100
    word1 and word2 consist of lowercase English letters.

*/

class Solution {
private:
    std::string twoPointer(std::string& word1, std::string& word2) {
        
        int p1 = 0;
        int p2 = 0;
        std::string s;
        while (p1 < word1.size() && p2 < word2.size()) {
            s += word1[p1];
            s += word2[p2];
            ++p1;
            ++p2;
        }

        while (p1 < word1.size()) {
            s += word1[p1];
            ++p1;
        } 

        while (p2 < word2.size()) {
            s += word2[p2];
            ++p2;
        } 

        return s;
    }

    std::string naive(string& word1, string& word2) {
        std::string r = "";
        int len = (word1.size() < word2.size()) ? word1.size() : word2.size();
        int i = 0;

        for (i = 0; i < len; ++i) {
            r += (char)word1[i];
            r += (char)word2[i];
        }

        std::string sub = "";
        if (word1.size() > len) {
            sub = word1.substr(i, word1.size() - len);
        } else if (word2.size() > len) {
            sub = word2.substr(i, word2.size() - len);
        }
       
        return r + sub;
    }
public:
    string mergeAlternately(string word1, string word2) {
        //return naive(word1, word2);
        return twoPointer(word1, word2);
    }
};