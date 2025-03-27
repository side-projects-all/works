/*
You are given an array of strings words and an integer k.

For each index i in the range [0, words.length - 1], find the length of the longest common

among any k strings (selected at distinct indices) from the remaining array after removing the ith element.

Return an array answer, where answer[i] is the answer for ith element. If removing the ith element leaves the array with fewer than k strings, answer[i] is 0.

 

Example 1:

Input: words = ["jump","run","run","jump","run"], k = 2

Output: [3,4,4,3,4]

Explanation:

    Removing index 0 ("jump"):
        words becomes: ["run", "run", "jump", "run"]. "run" occurs 3 times. Choosing any two gives the longest common prefix "run" (length 3).
    Removing index 1 ("run"):
        words becomes: ["jump", "run", "jump", "run"]. "jump" occurs twice. Choosing these two gives the longest common prefix "jump" (length 4).
    Removing index 2 ("run"):
        words becomes: ["jump", "run", "jump", "run"]. "jump" occurs twice. Choosing these two gives the longest common prefix "jump" (length 4).
    Removing index 3 ("jump"):
        words becomes: ["jump", "run", "run", "run"]. "run" occurs 3 times. Choosing any two gives the longest common prefix "run" (length 3).
    Removing index 4 ("run"):
        words becomes: ["jump", "run", "run", "jump"]. "jump" occurs twice. Choosing these two gives the longest common prefix "jump" (length 4).

Example 2:

Input: words = ["dog","racer","car"], k = 2

Output: [0,0,0]

Explanation:

    Removing any index results in an answer of 0.

 

Constraints:

    1 <= k <= words.length <= 10^5
    1 <= words[i].length <= 10^4
    words[i] consists of lowercase English letters.
    The sum of words[i].length is smaller than or equal 10^5.

*/

class Solution {
private:
    struct Trie_node {
        bool is_end;
        int pass_cnt;   //pass through this node and we count
        int links_cnt;
        Trie_node* subs[26]{ nullptr };
        Trie_node() : is_end{ false }, pass_cnt{ 0 }, links_cnt{ 0 } {

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
        std::map<int, int> possible_LCP;
        Trie_node* root;
        int k;
        Trie(int K) : k{ K } {
            root = new Trie_node();
        }

        void insert(const std::string& s) {
            Trie_node* now = root;
            int prefix_len = -1;
            for (int i = 0; i < s.size(); ++i) {
                if (!now->contains(s[i])) {
                    now->put(s[i]);
                }

                now = now->subs[s[i] - 'a'];
                ++now->pass_cnt;

                if (now->pass_cnt >= k) {
                    prefix_len = i + 1;
                }
            }

            if (prefix_len != -1) {
                ++possible_LCP[prefix_len];
            }
            now->is_end = true;
        }

        void remove(const std::string& s) {
            Trie_node* now = root;
            int prefix_len = -1;
            for (int i = 0; i < s.size(); ++i) {

                now = now->subs[s[i] - 'a'];
                

                if (now->pass_cnt >= k) {
                    prefix_len = i + 1;
                }

                --now->pass_cnt;
            }

            if (prefix_len != -1) {
                --possible_LCP[prefix_len];

                if (possible_LCP[prefix_len] == 0) {
                    possible_LCP.erase(prefix_len);
                }
            }
        }

        int LCP(const std::string& s) {
            int len = 0;
            int n = s.size();
            Trie_node* now = root;
            for (int i = 0; i < n; ++i) {
                if (now->contains(s[i]) && now->links_cnt == 1) {
                    now = now->subs[s[i] - 'a'];
                    ++len;
                }
            }

            return len;
        }
    };

    vector<int> by_trie(vector<string>& words, int& k) {
        
        int n = words.size();
        Trie trie(k);
        for (int i = 0; i < n; ++i) {
            trie.insert(words[i]);
        }

        std::vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            trie.remove(words[i]);
            ans[i] = trie.possible_LCP.empty() ? 0 : trie.possible_LCP.rbegin()->first;
            trie.insert(words[i]);
        }

        return ans;
    }
public:
    vector<int> longestCommonPrefix(vector<string>& words, int k) {
        return by_trie(words, k);
    }
};