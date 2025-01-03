
#include <string>

class Trie {
private:
    struct Node {
        bool isEnd = false;
        Node* next[26];

        Node() {
            
            for (int i = 0; i < 26; ++i) {
                    next[i] = nullptr;
            }
        }
    };

    Node root;
public:
    Trie() {
        //root = new Node();
    }
    
    void insert(const std::string& word);
    bool search(const std::string& word);
    bool startsWith(const std::string& prefix);
};