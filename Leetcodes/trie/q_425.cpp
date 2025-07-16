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

struct Node {
    Node* subs[26]{ nullptr };
    std::vector<int> indices;   //at this level, index of words uses this alphbet
    int link_cnt{ 0 };

    Node() {}

    void put(char c) {
        if (subs[c - 'a'] == nullptr) {
            subs[c - 'a'] = new Node();
            ++link_cnt;
        }
    }

    bool contain(char c) {
        return subs[c - 'a'] != nullptr;
    }
};

class Solution {
private:
    Node* root;
    void init(vector<string>& words) {
        root = new Node();

        for (int i = 0; i < words.size(); ++i) {

            Node* curr = root;
            for (int j = 0; j < words[i].size(); ++j) {

                if (!curr->contain(words[i][j])) {
                    curr->put(words[i][j]);
                }

                curr->indices.push_back(i);
                curr = curr->subs[words[i][j] - 'a'];
            }
        }
    }
    void backtracking(vector<string>& words, std::vector<std::vector<std::string>>& ans, 
        std::vector<std::string>& curr, int col) {
        
        if (col == words[0].size()) {
            ans.push_back(curr);
            return;
        }

        std::string col_word;
        for (std::string& s : curr) {
            col_word.push_back(s[col]);
        }

        Node* trie_node = root;
        for (char c : col_word) {
            if (!trie_node->contain(c)) {
                trie_node = nullptr;
                break;
            }

            trie_node = trie_node->subs[c - 'a'];
        }

        if (trie_node == nullptr) {
            return;
        }

        std::vector<int> indices = trie_node->indices;
        for (int i : indices) {
            curr.push_back(words[i]);
            backtracking(words, ans, curr, col + 1);
            curr.pop_back();
        }

    }
    vector<vector<string>> by_backtracking(vector<string>& words) {
        init(words);
        std::vector<std::vector<std::string>> ans;

        for (int i = 0; i < words.size(); ++i) {
            std::vector<std::string> curr{ words[i] };

            backtracking(words, ans, curr, 1);
        }

        return ans;
    }
public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        return by_backtracking(words);
    }
};