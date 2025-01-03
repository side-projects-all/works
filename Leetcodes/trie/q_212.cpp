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
    //trie node
    struct TrieNode {
        //bool isEnd;
        TrieNode* children[26];
        std::string word;

        TrieNode() {
            //isEnd = false;
            word = "";

            for (auto& child : children) {
                child = nullptr;
            }
        }
    };

    //trie root pointer
    TrieNode* root;

    //four directions: left, up, right, down
    int dir[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

    //build trie
    void createTrie(const std::vector<string>& words) {
        root = new TrieNode();
        TrieNode* now = root;

        for (auto& w : words) {

            for (char c : w) {

                int i = c - 'a';
                if (now->children[i] == nullptr) {
                    now->children[i] = new TrieNode();
                }
                now = now->children[i];
            }

            //now->isEnd = true;
            now->word = w;
            now = root;
        }
    }

    //backtracking method
    void backtracking(std::vector<std::vector<char>>& board, TrieNode* parent,
                                            int row, int col, std::vector<std::string>& result) {

        char letter = board[row][col];  //for temporary store of the character we will explore
        TrieNode* now = parent;

        if (now->word != "") {
            result.push_back(now->word);
            now->word = "";
        }

        board[row][col] = '#';  //temporarily marks this letter

        for (int i = 0; i < 4; ++i) {
            int r = row + dir[i][0];
            int c = col + dir[i][1];

            if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size()) {
                continue;
            }

            int index = board[r][c] - 'a';
            //for the letter that was changed to #
            if (index >= 0 && now->children[index] != nullptr) {
                backtracking(board, now->children[index], r, c, result);
            }
        }

        board[row][col] = letter;   //recover this letter
    }

public:
    std::vector<std::string> findWords(vector<vector<char>>& board, vector<string>& words) {
        createTrie(words);

        std::vector<std::string> result;
        for (int r = 0; r < board.size(); ++r) {
            for (int c = 0; c < board[0].size(); ++c) {
                int i = board[r][c] - 'a';
                if (root->children[i] != nullptr) {
                    backtracking(board, root->children[i], r, c, result);
                }
            }
        }
        return result;
    }
};