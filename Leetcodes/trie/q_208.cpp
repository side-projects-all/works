/*
A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.

Implement the Trie class:

    Trie() Initializes the trie object.
    void insert(String word) Inserts the string word into the trie.
    boolean search(String word) Returns true if the string word is in the trie (i.e., was inserted before), and false otherwise.
    boolean startsWith(String prefix) Returns true if there is a previously inserted string word that has the prefix prefix, and false otherwise.

 

Example 1:

Input
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
Output
[null, null, true, false, true, null, true]

Explanation
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // return True
trie.search("app");     // return False
trie.startsWith("app"); // return True
trie.insert("app");
trie.search("app");     // return True

 

Constraints:

    1 <= word.length, prefix.length <= 2000
    word and prefix consist only of lowercase English letters.
    At most 3 * 104 calls in total will be made to insert, search, and startsWith.


*/

class Trie {
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

        bool contains(char c) {
            return subs[c - 'a'] != nullptr;
        }

        void put(char c, Trie_node* node) {
            if (subs[c - 'a'] == nullptr) {
                subs[c - 'a'] = node;
                ++links_cnt;
            }
        }

        int get_links_cnt() const {
            return links_cnt;
        }
    };

    Trie_node* root;
public:
    Trie() {
        root = new Trie_node();
    }
    
    void insert(string word) {
        Trie_node* node = root;

        for (int i = 0; i < word.size(); ++i) {
            if (!node->contains(word[i])) {
                node->put(word[i], new Trie_node());
            }

            node = node->subs[word[i] - 'a'];
        }

        node->is_end = true;
    }
    
    bool search(string word) {
        Trie_node* node = root;

        for (int i = 0; i < word.size(); ++i) {
            if (!node->contains(word[i])) {
                return false;
            }

            node = node->subs[word[i] - 'a'];
        }


        return node->is_end;
    }
    
    bool startsWith(string prefix) {
        Trie_node* node = root;

        for (int i = 0; i < prefix.size(); ++i) {
            if (!node->contains(prefix[i])) {
                return false;
            }

            node = node->subs[prefix[i] - 'a'];
        }

        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */