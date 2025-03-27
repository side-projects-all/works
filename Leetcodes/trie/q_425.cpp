/*
Given an array of unique strings words, return all the word squares you can build from words. The same word from words can be used multiple times. You can return the answer in any order.

A sequence of strings forms a valid word square if the kth row and column read the same string, where 0 <= k < max(numRows, numColumns).

    For example, the word sequence ["ball","area","lead","lady"] forms a word square because each word reads the same both horizontally and vertically.

 

Example 1:

Input: words = ["area","lead","wall","lady","ball"]
Output: [["ball","area","lead","lady"],["wall","area","lead","lady"]]
Explanation:
The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).

Example 2:

Input: words = ["abat","baba","atan","atal"]
Output: [["baba","abat","baba","atal"],["baba","abat","baba","atan"]]
Explanation:
The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).

 

Constraints:

    1 <= words.length <= 1000
    1 <= words[i].length <= 4
    All words[i] have the same length.
    words[i] consists of only lowercase English letters.
    All words[i] are unique.


*/

class Solution {
private:
    struct Trie_node {
        std::vector<int> str_indices;   //string index using this character
        Trie_node* subs[26];
        int links_cnt;

        Trie_node() : links_cnt{ 0 } {
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

        void insert(vector<string>& words) {
            Trie_node* now;

            for (int i = 0; i < words.size(); ++i) {

                now = root;
                for (int j = 0; j < words[i].size(); ++j) {
                    if (!now->contains(words[i][j])) {
                        now->put(words[i][j], new Trie_node());
                    }

                    now = now->subs[words[i][j] - 'a'];
                    now->str_indices.push_back(i);
                }
            }
        }
    };
    void back_tracking(Trie_node* root, vector<string>& words, std::vector<std::vector<std::string>>& ans, 
                                                    int col, std::vector<std::string>& sqr) {
        if (col == words[0].size()) {
            ans.push_back(sqr);
            return;
        }

        std::string col_chars;
        for (std::string& s : sqr) {
            //when you at column 1, you will have 1 string; column 2, 2 strings, column 3, 3 strings
            col_chars += s[col];    
        }

        //using the symmetry to compare in trie
        Trie_node* now = root;
        for (char c : col_chars) {
            if (!now->contains(c)) {
                now = nullptr;  //this is necessary!!!
                break;
            }

            now = now->subs[c - 'a'];
        }

        std::vector<int> indices;
        if (now != nullptr) {
            indices = now->str_indices;
        }

        for (int i : indices) {
            sqr.push_back(words[i]);
            back_tracking(root, words, ans, col + 1, sqr);
            sqr.pop_back();
        }
    }

    vector<vector<string>> by_trie_back_tracking(vector<string>& words) {
        std::vector<std::vector<std::string>> ans;
        Trie trie;
        trie.insert(words);
        
        for (int i = 0; i < words.size(); ++i) {
            std::vector<std::string> sqr{ words[i] };
            back_tracking(trie.root, words, ans, 1, sqr);
        }

        return ans;
    }
public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        return by_trie_back_tracking(words);
    }
};