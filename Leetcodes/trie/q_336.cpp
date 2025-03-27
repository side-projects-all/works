/*
You are given a 0-indexed array of unique strings words.

A palindrome pair is a pair of integers (i, j) such that:

    0 <= i, j < words.length,
    i != j, and
    words[i] + words[j] (the concatenation of the two strings) is a 

    .

Return an array of all the palindrome pairs of words.

You must write an algorithm with O(sum of words[i].length) runtime complexity.

 

Example 1:

Input: words = ["abcd","dcba","lls","s","sssll"]
Output: [[0,1],[1,0],[3,2],[2,4]]
Explanation: The palindromes are ["abcddcba","dcbaabcd","slls","llssssll"]

Example 2:

Input: words = ["bat","tab","cat"]
Output: [[0,1],[1,0]]
Explanation: The palindromes are ["battab","tabbat"]

Example 3:

Input: words = ["a",""]
Output: [[0,1],[1,0]]
Explanation: The palindromes are ["a","a"]

 

Constraints:

    1 <= words.length <= 5000
    0 <= words[i].length <= 300
    words[i] consists of lowercase English letters.

*/

class Solution {
private:
    struct TrieNode {
        std::vector<int> plaindromePrefixRemaining; //because the required out are indice
        int theEndWordIndex = -1;
        TrieNode* children[26];

        TrieNode() {
            
            for (auto& child : children) {
                child = nullptr;
            }
        }
    };

    TrieNode* root;

    void createReverseTrie(std::vector<std::string>& words) {
        root = new TrieNode();
        TrieNode* now;

        for (int j = 0; j < words.size(); ++j) {       
            
            now = root;
            std::string reverse = words[j];
            std::reverse(reverse.begin(), reverse.end());   //set the string in reverse way

            for (int i = 0; i < words[j].size(); ++i) {

                //if we could find a palindrome in reverse from position i, 
                //we add the index j of that word
                if (hasPalindromeRemaining(reverse, i)) {
                    now->plaindromePrefixRemaining.push_back(j);
                }

                //put every letter of the word in reverse way into the Trie node
                int index = reverse[i] - 'a';
                if (now->children[index] == nullptr) {
                    now->children[index] = new TrieNode();
                }

                now = now->children[index];
            }

            now->theEndWordIndex = j;
        }
    }

    bool hasPalindromeRemaining(std::string& s, int i) {
        int p01 = i;
        int p02 = s.size() - 1;

        while (p01 < p02) {
            if (s[p01] != s[p02]) {
                return false;
            }

            ++p01;
            --p02;
        }

        return true;
    }

public:
    vector<vector<int>> palindromePairs(vector<string>& words) {

        //build trie first
        createReverseTrie(words);

        //search trie
        std::vector<std::vector<int>> result;
        TrieNode* now;

        for (int wIndex = 0; wIndex < words.size(); ++wIndex) {
            now = root;

            //loop through every word and divided into three cases to find palindrome
            for (int ch = 0; ch < words[wIndex].size(); ++ch) {

                //for case 3
                if (now->theEndWordIndex != -1 && hasPalindromeRemaining(words[wIndex], ch)) {
                    result.push_back({wIndex, now->theEndWordIndex});
                }

                int i = words[wIndex][ch] - 'a';
                //need to move the pointer to children first, 
                //or something will be wrong in the following case 2
                now = now->children[i];
                
                if (now == nullptr) {
                    break;
                }
            }

            if (now == nullptr) {
                continue;
            }

            //for case 1
            if (now->theEndWordIndex != -1 && now->theEndWordIndex != wIndex) {
                result.push_back({wIndex, now->theEndWordIndex});
            }

            //for case 2
            for (int other : now->plaindromePrefixRemaining) {
                result.push_back({wIndex, other});
            }
        }

        return result;
    }
};