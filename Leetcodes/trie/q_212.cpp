/*
Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

 

Example 1:

Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]

Example 2:

Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []

 

Constraints:

    m == board.length
    n == board[i].length
    1 <= m, n <= 12
    board[i][j] is a lowercase English letter.
    1 <= words.length <= 3 * 104
    1 <= words[i].length <= 10
    words[i] consists of lowercase English letters.
    All the strings of words are unique.


*/

class Solution {
private:
    struct Trie_node {
        std::string word;
        int links_cnt;
        Trie_node* subs[26];

        Trie_node() : word{ "" }, links_cnt{ 0 } {
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
        int get_links_cnt() const {
            return links_cnt;
        }
    };

    struct Trie {
    private:
        Trie_node* root;
    public:
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

            now->word = s;
        }

        Trie_node* search_char_by_node(char c, Trie_node* node) {
            return node->subs[c - 'a'];
        }

        Trie_node* get_root() {
            return root;
        }
    };

    void back_tracking(vector<vector<char>>& board, std::vector<std::string>& ans, Trie_node* pos, int r, int c) {
        if (pos->word != "") {
            ans.push_back(pos->word);
            pos->word = "";     //marked empty if used, and do not just return!
        }

        int rows = board.size();
        int cols = board[0].size();

        char tmp = board[r][c];
        board[r][c] = '#';
        if (r + 1 < rows && board[r + 1][c] != '#' && pos->contains(board[r + 1][c])) {
            back_tracking(board, ans, pos->subs[board[r + 1][c] - 'a'], r + 1, c);
        }

        if (r - 1 >= 0 && board[r - 1][c] != '#' && pos->contains(board[r - 1][c])) {
            back_tracking(board, ans, pos->subs[board[r - 1][c] - 'a'], r - 1, c);
        }

        if (c + 1 < cols && board[r][c + 1] != '#' && pos->contains(board[r][c + 1])) {
            back_tracking(board, ans, pos->subs[board[r][c + 1] - 'a'], r, c + 1);
        }

        if (c - 1 >= 0 && board[r][c - 1] != '#' && pos->contains(board[r][c - 1])) {
            back_tracking(board, ans, pos->subs[board[r][c - 1] - 'a'], r, c - 1);
        }

        board[r][c] = tmp;
    }
    vector<string> by_trie_back_tracking(vector<vector<char>>& board, vector<string>& words) {
        Trie trie;

        //build trie
        for (int i = 0; i < words.size(); ++i) {
            trie.insert(words[i]);
        }

        //do back_tracking
        std::vector<std::string> ans;
        Trie_node* now = trie.get_root();

        for (int r = 0; r < board.size(); ++r) {
            for (int c = 0; c < board[0].size(); ++c) {
                if (trie.search_char_by_node(board[r][c], now) != nullptr) {
                    back_tracking(board, ans, now->subs[board[r][c] - 'a'], r, c);
                }
            }
        }

        return ans;
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        return by_trie_back_tracking(board, words);
    }
};