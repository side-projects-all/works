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
    struct Node {
        bool isEnd;
        Node* links[26]; //using pointer array is faster than unordered_map!!!!

        Node() {
            isEnd = false;
            for (auto& link : links) {
                link = nullptr;
            }
        }
    };

    Node root;

public:
    Trie() {
        
    }
    
    void insert(string word) {
        Node* n = &root;
        
        for (auto& ch : word) {
            int i = ch - 'a';

            if (n->links[i] == nullptr) {
                n->links[i] = new Node();
            }

            n = n->links[i];
        }

        n->isEnd = true;
    }
    
    bool search(string word) {
        Node* n = &root;

        for (auto& ch : word) {
            int i = ch - 'a';

            if (n->links[i] == nullptr) {
                return false;
            }

            n = n->links[i];
        }

        //check if word was just prefix
        return (n->isEnd) ? true : false;
    }
    
    bool startsWith(string prefix) {
        Node* n = &root;

        for (const auto& ch : prefix) {
            int i = ch - 'a';

            if (n->links[i] == nullptr) {
                return false;
            }

            n = n->links[i];
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