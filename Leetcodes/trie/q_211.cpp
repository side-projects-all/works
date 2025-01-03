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
    struct TrieNode {
        //std::string val;
        bool isEnd;
        static const int arr_len = 26;
        TrieNode* subs[arr_len];

        TrieNode () {
            isEnd = false;

            for (auto& s : subs) {
                s = nullptr;
            }
        }
    };

    TrieNode* root;

    //this is the hardest part of this question
    //when you met dot(.), how you handle it?
    //here, i did it by resursive way.
    //could we change it into iterative way?
    bool checkChildren(TrieNode* ptr, std::string word) {
        
        TrieNode* n = ptr;

        if (word.length() == 0) {
            return ptr->isEnd;
        }

        char ch = word[0];
        if (ch == '.') {
            for (TrieNode* p : ptr->subs) {
                if (p != nullptr && checkChildren(p, word.substr(1))) {
                    return true;
                }
            }
        } else if (ptr->subs[ch - 'a'] != nullptr) {
            TrieNode* next = ptr->subs[ch - 'a'];
            return checkChildren(next, word.substr(1));
        }

        return false;
    }

public:
    WordDictionary() {
        root = new TrieNode();
    }
    
    void addWord(string word) {
        TrieNode* n = root;

        for (char c : word) {
            int i = c - 'a';
            
            if (n->subs[i] == nullptr) {
                n->subs[i] = new TrieNode();
            }

            n = n->subs[i];
        }

        n->isEnd = true;
    }
    
    bool search(string word) {
        
        return checkChildren(root, word);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */