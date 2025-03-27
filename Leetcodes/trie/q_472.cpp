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
private:
    struct Trie_node {
        bool is_end;
        int links_cnt;
        Trie_node* subs[26];
        Trie_node() : is_end{ false }, links_cnt{ 0 } {
            for (int i = 0; i < 26; ++i) {
                subs[i] = nullptr;
            }
        }

        void put(char c, Trie_node* node) {
            if (subs[c - 'a'] == nullptr) {
                subs[c - 'a'] = node;
                ++links_cnt;
            }
        }

        bool contains(char c) {
            return subs[c - 'a'] != nullptr;
        }
    };

    struct Trie {
        Trie_node* root;
        Trie() {
            root = new Trie_node();
        }

        void insert(const std::string& s) {
            Trie_node* now = root;
            for (int i = 0; i < s.size(); ++i) {
                if (!now->contains(s[i])) {
                    now->put(s[i], new Trie_node());
                }

                now = now->subs[s[i] - 'a'];
            }

            now->is_end = true;
        }

        bool search(const std::string& s) {
            Trie_node* now = root;
            for (int i = 0; i < s.size(); ++i) {
                if (!now->contains(s[i])) {
                    return false;
                }

                now = now->subs[s[i] - 'a'];
            }

            return now->is_end;
        }
    };

    bool recursive_with_trie(Trie& trie, std::string& curr, std::unordered_map<std::string, bool>& mem) {
        
        if (mem.find(curr) != mem.end()) {
            return mem[curr];
        }

        for (int i = 1; i < curr.size(); ++i) {
            std::string pre = curr.substr(0, i);
            std::string rest = curr.substr(i);

            if (trie.search(pre) && (trie.search(rest) || recursive_with_trie(trie, rest, mem))) {
                return mem[curr] = true;
            }
        }

        return mem[curr] = false;
    }
    vector<string> by_trie_dfs(vector<string>& words) {
        //build trie
        Trie trie;
        for (int i = 0; i < words.size(); ++i) {
            trie.insert(words[i]);
        }

        std::unordered_map<std::string, bool> mem;
        std::vector<string> ans;
        for (int i = 0; i < words.size(); ++i) {
            
            if (recursive_with_trie(trie, words[i], mem)) {
                ans.push_back(words[i]);
            }
        }

        return ans;
    }
    bool recursive_with_set(std::unordered_set<std::string>& set, std::unordered_map<std::string, bool>& mem, std::string& curr) {
        
        if (mem.find(curr) != mem.end()) {
            return mem[curr];
        }

        //divide prefix and rest in every len
        for (int len = 1; len < curr.size(); ++len) {
            std::string pre = curr.substr(0, len);
            std::string rest = curr.substr(len);

            if (set.find(pre) != set.end() && (set.find(rest) != set.end() || recursive_with_set(set, mem, rest))) {
                return mem[curr] = true;
            }
        }

        return mem[curr] = false;
    }
    vector<string> by_set_recursive_dp(vector<string>& words) {
        std::unordered_set<std::string> set{words.begin(), words.end()};
        //for all length substring if in set
        std::unordered_map<std::string, bool> mem;
        std::vector<string> ans;
        for (int i = 0; i < words.size(); ++i) {
            
            if (recursive_with_set(set, mem, words[i])) {
                ans.push_back(words[i]);
            }
        }

        return ans;
    }

    vector<string> by_set_iterative_dp(vector<string>& words) {
        std::unordered_set<std::string> set{words.begin(), words.end()};

        std::vector<string> ans;
        for (int i = 0; i < words.size(); ++i) {

            int n = words[i].size();
            std::vector<bool> dp(n + 1);
            dp[0] = true;

            for (int len = 1; len <= n; ++len) {

                //using (len == n ? 1 : 0) could excluding the calculation of combination of 0 and n
                //because we only want effective combination
                //!dp[len] means if we did not find right combination, we continue to split
                for (int j = (len == n ? 1 : 0); !dp[len] && j < len; ++j) {
                    //the total length result depending on prefix and rest substring in set or not
                    dp[len] = dp[j] && (set.find(words[i].substr(j, len - j)) != set.end());
                }
            }

            if (dp[n]) {
                ans.push_back(words[i]);
            }
        }

        return ans;
    }

    vector<string> by_trie_iterative_dp(vector<string>& words) {
        //build trie
        Trie trie;
        for (int i = 0; i < words.size(); ++i) {
            trie.insert(words[i]);
        }
        
        std::vector<string> ans;
        for (int i = 0; i < words.size(); ++i) {

            int n = words[i].size();
            std::vector<bool> dp(n + 1);
            dp[0] = true;

            for (int len = 1; len <= n; ++len) {

                //using (len == n ? 1 : 0) could excluding the calculation of combination of 0 and n
                //because we only want the combination
                for (int j = (len == n ? 1 : 0); !dp[len] && j < len; ++j) {
                    //the total length result depending on prefix and rest substring in set or not
                    dp[len] = dp[j] && trie.search(words[i].substr(j, len - j));
                }
            }

            if (dp[n]) {
                ans.push_back(words[i]);
            }
        }

        return ans;
    }
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        //return by_set_recursive_dp(words);
        //return by_trie_dfs(words);
        
        return by_set_iterative_dp(words);
        //return by_trie_iterative_dp(words);
    }
};
