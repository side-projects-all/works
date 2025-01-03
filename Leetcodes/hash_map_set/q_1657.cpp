/*
Two strings are considered close if you can attain one from the other using the following operations:

    Operation 1: Swap any two existing characters.
        For example, abcde -> aecdb
    Operation 2: Transform every occurrence of one existing character into another existing character, and do the same with the other character.
        For example, aacabb -> bbcbaa (all a's turn into b's, and all b's turn into a's)

You can use the operations on either string as many times as necessary.

Given two strings, word1 and word2, return true if word1 and word2 are close, and false otherwise.

 

Example 1:

Input: word1 = "abc", word2 = "bca"
Output: true
Explanation: You can attain word2 from word1 in 2 operations.
Apply Operation 1: "abc" -> "acb"
Apply Operation 1: "acb" -> "bca"

Example 2:

Input: word1 = "a", word2 = "aa"
Output: false
Explanation: It is impossible to attain word2 from word1, or vice versa, in any number of operations.

Example 3:

Input: word1 = "cabbba", word2 = "abbccc"
Output: true
Explanation: You can attain word2 from word1 in 3 operations.
Apply Operation 1: "cabbba" -> "caabbb"
Apply Operation 2: "caabbb" -> "baaccc"
Apply Operation 2: "baaccc" -> "abbccc"

 

Constraints:

    1 <= word1.length, word2.length <= 10^5
    word1 and word2 contain only lowercase English letters.


*/

class Solution {
public:
    bool closeStrings(string word1, string word2) {
        std::unordered_map<char, int> m1;
        std::unordered_map<char, int> m2;

        for (char c : word1) {
            ++m1[c];
        }

        for (char c : word2) {
            if (m1.find(c) == m1.end()) {
                return false;
            }
            ++m2[c];
        }

        if (m1.size() != m2.size()) {
            return false;
        }

        std::vector<int> v1(m1.size());
        std::vector<int> v2(m2.size());

        int i = 0;
        for (auto& p : m1) {
            v1[i] = p.second;
            ++i;
        }
        i = 0;
        for (auto& p : m2) {
            v2[i] = p.second;
            ++i;
        }
        
        std::sort(v1.begin(), v1.end());
        std::sort(v2.begin(), v2.end());
        for (int i = 0; i < v1.size(); ++i) {
            if (v1[i] != v2[i]) {
                return false;
            }
        }

        return true;
    }
};