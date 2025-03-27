/*
Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

 

Example 1:

Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".

Example 2:

Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.

Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false

 

Constraints:

    1 <= s.length <= 300
    1 <= wordDict.length <= 1000
    1 <= wordDict[i].length <= 20
    s and wordDict[i] consist of only lowercase English letters.
    All the strings of wordDict are unique.


*/

class Solution {
private:
    struct Trie_node {
        bool is_end;
        int links_cnt;
        Trie_node* subs[26]{ nullptr };
        Trie_node() : is_end{ false }, links_cnt{ 0 } {

        }

        void put(char c) {
            if (subs[c - 'a'] == nullptr) {
                subs[c - 'a'] = new Trie_node();
                ++links_cnt;
            }
        }

        bool contains(char c) {
            return subs[c - 'a'] != nullptr;
        }
    };

    struct Trie {
        Trie_node* root{ new Trie_node() };
        Trie() {

        }

        void insert(const std::string& s) {
            Trie_node* now = root;
            for (int i = 0; i < s.size(); ++i) {
                if (!now->contains(s[i])) {
                    now->put(s[i]);
                }

                now = now->subs[s[i] - 'a'];
            }

            now->is_end = true;
        }
    };
    bool by_trie_iterative_dp(string& s, vector<string>& wordDict) {
        
        //build trie
        Trie trie;
        for (int i = 0; i < wordDict.size(); ++i) {
            trie.insert(wordDict[i]);
        }

        //search in trie
        int n = s.size();
        std::vector<bool> dp(n);
        Trie_node* now;
        for (int i = 0; i < n; ++i) {

            if (i == 0 || dp[i - 1]) {

                now = trie.root;
                for (int j = i; j < n; ++j) {
                    if (!now->contains(s[j])) {
                        break;
                    }

                    now = now->subs[s[j] - 'a'];
                    if (now->is_end) {
                        dp[j] = true;
                    }
                }
            }
        }

        return dp[n - 1];
    }
    bool by_iterative_dp(string& s, vector<string>& wordDict) {
        int n = s.size();
        std::vector<bool> dp(n);

        for (int i = 0; i < n; ++i) {

            for (int w = 0; w < wordDict.size(); ++w) {
                if (i < wordDict[w].size() - 1) {
                    continue;
                }

                if (i == wordDict[w].size() - 1 || dp[i - wordDict[w].size()]) {
                    if (s.substr(i - wordDict[w].size() + 1, wordDict[w].size()) == wordDict[w]) {
                        dp[i] = true;
                        break;
                    }
                }
            }
        }
        return dp[n - 1];
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        //return by_iterative_dp(s, wordDict);
        
        return by_trie_iterative_dp(s, wordDict);
    }
};