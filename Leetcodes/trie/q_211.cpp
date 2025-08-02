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

struct Node {
    bool is_end{false};
    Node* subs[26]{nullptr};
    int link_cnt{0};
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

static inline bool find_word(string &word, int pos, Node *curr) {
    int n = word.size();

    for (int i = pos; i < n; ++i) {
        if (word[i] == '.') {

            for (char c = 'a'; c <= 'z'; ++c) {
                if (curr->subs[c - 'a'] != nullptr && find_word(word, i + 1, curr->subs[c - 'a'])) {
                    return true;
                }
            }
            return false;

        } else {

            if (!curr->contain(word[i])) return false;

            curr = curr->subs[word[i] - 'a'];
        }
    }

    return curr->is_end;
}

class WordDictionary {
private:
    Node *root;
public:
    WordDictionary() {
        root = new Node();
    }
    
    void addWord(string word) {
        Node *curr = root;
        int n = word.size();
        for (int i = 0; i < n; ++i) {
            if (!curr->contain(word[i])) {
                curr->put(word[i]);
            }

            curr = curr->subs[word[i] - 'a'];
        }

        curr->is_end = true;
    }
    
    bool search(string word) {
        return find_word(word, 0, root);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */