/*
Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.

A concatenated word is defined as a string that is comprised entirely of at least two shorter words (not necessarily distinct) in the given array.

 

Example 1:

Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
"dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
"ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".

Example 2:

Input: words = ["cat","dog","catdog"]
Output: ["catdog"]

 

Constraints:

    1 <= words.length <= 10^4
    1 <= words[i].length <= 30
    words[i] consists of only lowercase English letters.
    All the strings of words are unique.
    1 <= sum(words[i].length) <= 10^5


*/

class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        return by_dfs(words);
        //return by_dp(words);
    }

private:
    std::vector<string> by_dp(std::vector<string>& words) {
        std::unordered_set<std::string> set(words.begin(), words.end());
        std::vector<string> ans;

        for (const string& word : words) {

            const int len = word.size();
            std::vector<bool> dp(len + 1);
            dp[0] = true;

            for (int i = 1; i <= len; ++i) {
                for (int j = (i == len ? 1 : 0); !dp[i] && j < i; ++j) {
                    dp[i] = dp[j] && set.count(word.substr(j, i - j));
                }
            }
            if (dp[len]) {
                ans.push_back(word);
            }
        }
        return ans;
    }

    // check if a word can be formed by other words
    bool dfs(const std::string& word, const std::unordered_set<std::string>& set, 
                                        std::unordered_map<std::string, bool>& mem) {
        // return if  in memo
        if (mem.find(word) != mem.end()) {
            return mem[word];
        }

        // split the word at every possible prefix length
        for (int i = 1; i < word.size(); ++i) {
            std::string prefix = word.substr(0, i);
            std::string suffix = word.substr(i);
            
            // If the prefix is a word and the suffix can be formed by other words, mark this word as valid
            if (set.count(prefix) && (set.count(suffix) || dfs(suffix, set, mem))) {
                mem[word] = true;
                return true;
            }
        }
    
        return mem[word] = false;
    }

    std::vector<std::string> by_dfs(std::vector<std::string>& words) {
        std::unordered_set<std::string> set(words.begin(), words.end());
        std::unordered_map<std::string, bool> memo;
        std::vector<std::string> ans;
        
        // Check each word in the list
        for (const std::string& w : words) {
            if (dfs(w, set, memo)) {
                ans.push_back(w);
            }
        }
        
        return ans;
    }
};
