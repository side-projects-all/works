/*
You are given an array of words where each word consists of lowercase English letters.

wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in wordA without changing the order of the other characters to make it equal to wordB.

    For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad".

A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1 is a predecessor of word2, word2 is a predecessor of word3, and so on. A single word is trivially a word chain with k == 1.

Return the length of the longest possible word chain with words chosen from the given list of words.

 

Example 1:

Input: words = ["a","b","ba","bca","bda","bdca"]
Output: 4
Explanation: One of the longest word chains is ["a","ba","bda","bdca"].

Example 2:

Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
Output: 5
Explanation: All the words can be put in a word chain ["xb", "xbc", "cxbc", "pcxbc", "pcxbcf"].

Example 3:

Input: words = ["abcd","dbqca"]
Output: 1
Explanation: The trivial word chain ["abcd"] is one of the longest word chains.
["abcd","dbqca"] is not a valid word chain because the ordering of the letters is changed.

 

Constraints:

    1 <= words.length <= 1000
    1 <= words[i].length <= 16
    words[i] only consists of lowercase English letters.


*/

class Solution {
private:
    int iterative(std::vector<string>& words) {
        std::unordered_set<std::string> existed;

        for (int i = 0; i < words.size(); ++i) {
            existed.insert(words[i]);
        }

        std::sort(words.begin(), words.end(), [](const std::string& s1, const std::string s2) {
            return s1.size() < s2.size();
        });

        std::unordered_map<std::string, int> mem;

        mem[words[0]] = 1;
        
        int arrMaxLen = 1;
        for (int i = 1; i < words.size(); ++i) {
            std::string curr = words[i];
            
            int currMaxLen = 1;

            for (int c = 0; c < curr.size(); ++c) {
                std::string sub = curr.substr(0, c) + curr.substr(c + 1);

                //if we find this sub-string in set, we do recursive operation
                if (existed.find(sub) != existed.end()) {
                    
                    currMaxLen = std::max(currMaxLen, 1 + mem[sub]);
                }
            }
            mem[curr] = currMaxLen;
            arrMaxLen = std::max(arrMaxLen, currMaxLen);
        }

        return arrMaxLen;
    }

    int recursive(std::unordered_set<std::string>& existed, std::string curr, 
                                            std::unordered_map<std::string, int>& mem) {

        //base case
        if (curr.size() == 1) {
            return 1;
        }

        if (mem.find(curr) != mem.end()) {
            return mem[curr];
        }

        int currMaxLen = 1;

        int currLen = 0;
        for (int i = 0; i < curr.size(); ++i) {
            std::string sub = curr.substr(0, i) + curr.substr(i + 1);

            //if we find this sub-string in set, we do recursive operation
            if (existed.find(sub) != existed.end()) {
                
                currLen = std::max(currLen, 1 + recursive(existed, sub, mem));
            }

        }

        currMaxLen = std::max(currMaxLen, currLen);
        mem[curr] = currMaxLen;

        return currMaxLen;
    }
public:
    int longestStrChain(vector<string>& words) {
        /*
        std::unordered_set<std::string> existed;

        for (int i = 0; i < words.size(); ++i) {
            existed.insert(words[i]);
        }

        std::unordered_map<std::string, int> mem;

        int maxLen = 0;
        for (auto& w : words) {
            maxLen = std::max(maxLen, recursive(existed, w, mem));
        }

        return maxLen;
        */

        return iterative(words);
    }
};