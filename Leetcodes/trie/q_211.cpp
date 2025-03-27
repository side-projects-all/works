/*
Design a data structure that supports adding new words and finding if a string matches any previously added string.

Implement the WordDictionary class:

    WordDictionary() Initializes the object.
    void addWord(word) Adds word to the data structure, it can be matched later.
    bool search(word) Returns true if there is any string in the data structure that matches word or false otherwise. word may contain dots '.' where dots can be matched with any letter.

 

Example:

Input
["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
[[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
Output
[null,null,null,null,false,true,true,true]

Explanation
WordDictionary wordDictionary = new WordDictionary();
wordDictionary.addWord("bad");
wordDictionary.addWord("dad");
wordDictionary.addWord("mad");
wordDictionary.search("pad"); // return False
wordDictionary.search("bad"); // return True
wordDictionary.search(".ad"); // return True
wordDictionary.search("b.."); // return True

 

Constraints:

    1 <= word.length <= 25
    word in addWord consists of lowercase English letters.
    word in search consist of '.' or lowercase English letters.
    There will be at most 2 dots in word for search queries.
    At most 104 calls will be made to addWord and search.


*/

class WordDictionary {
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

        int get_links_cnt() const {
            return link_cnt;
        }
    };

    struct Trie {
        public:
            Trie_node* root;

            Trie() {
                root = new Trie_node();
            }

            void insert(std::string& str) {
                int n = str.size();
                Trie_node* node = root;

                for (int i = 0; i < n; ++i) {
                    if (!node->contains(str[i])) {
                        node->put(str[i], new Trie_node());
                    }

                    node = node->subs[str[i] - 'a'];
                }

                node->is_end = true;
            }

            bool has_word(std::string& str, Trie_node* now) {
                int n = str.size();
                Trie_node* node = now;

                for (int i = 0; i < n; ++i) {
                    if (str[i] == '.') {

                        std::string rest = str.substr(i + 1);
                        for (int j = 0; j < 26; ++j) {
                            if (node->subs[j] != nullptr && has_word(rest, node->subs[j])) {
                                return true;
                            }
                        }

                        return false;

                    } else {
                        if (!node->contains(str[i])) {
                            return false;

                        } else {
                            node = node->subs[str[i] - 'a'];
                        }
                    }
                }

                return node->is_end;
            }
    };

    Trie trie;
public:
    WordDictionary() {
        
    }
    
    void addWord(string word) {
        trie.insert(word);
    }
    
    bool search(string word) {
        return trie.has_word(word, trie.root);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */