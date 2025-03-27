/*
Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

 

Example 1:

Input: strs = ["flower","flow","flight"]
Output: "fl"

Example 2:

Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.

 

Constraints:

    1 <= strs.length <= 200
    0 <= strs[i].length <= 200
    strs[i] consists of only lowercase English letters.


*/

class Solution {
private:
    struct Trie_node {
        bool is_end;
        int link_cnt;
        Trie_node* subs[26];

        Trie_node() : is_end{ false }, link_cnt{ 0 } {
            for (int i = 0; i < 26; ++i) {
                subs[i] = nullptr;
            }
        }

        void put(char c, Trie_node* node) {
            if (subs[c - 'a'] == nullptr) {
                subs[c - 'a'] = node;
                ++link_cnt;
            }
        }

        bool contains(char c) {
            return subs[c - 'a'] != nullptr;
        }

        int get_link_cnt() const {
            return link_cnt;
        }
    };

    struct Trie {
        Trie_node* root;
        Trie() {
            root = new Trie_node();
        }

        void insert(const std::string& word) {
            Trie_node* node = root;

            for (char c : word) {
                if (!node->contains(c)) {
                    node->put(c, new Trie_node());
                }

                node = node->subs[c - 'a'];
            }

            node->is_end = true;
        }

        std::string LCP(const std::string& word) {
            Trie_node* node = root;
            std::string prefix;

            for (char c : word) {
                if (node->contains(c) && node->get_link_cnt() == 1 && !node->is_end) {
                    prefix.push_back(c);
                    node = node->subs[c - 'a'];

                } else {
                    break;
                }
            }

            return prefix;
        }
    };
    std::string by_trie(vector<string>& strs) {
        int n = strs.size();
        if (n == 1) {
            return strs[0];
        }

        Trie trie;
        for (int i = 0; i < n; ++i) {
            trie.insert(strs[i]);
        }

        return trie.LCP(strs[0]);
    }

    std::string by_vertical_compare(vector<string>& strs) {

        //vertical
        for (int i = 0; i < strs[0].size(); ++i) {
            char c = strs[0][i];

            for (int p = 1; p < strs.size(); ++p) {
                if (i == strs[p].size() || strs[p][i] != c) {
                    return strs[0].substr(0, i);
                }
            }
        }

        return strs[0];
    }
public:
    string longestCommonPrefix(vector<string>& strs) {
        //return by_vertical_compare(strs);
        return by_trie(strs);
    }
};