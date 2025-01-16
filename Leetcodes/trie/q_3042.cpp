/*

*/

class Node {
private:
    Node* links[26]{ nullptr };

public:
    bool contains(char c) {
        return links[c - 'a'] != nullptr;
    }

    void put(char c, Node* n) {
        links[c - 'a'] = n;
    }

    Node* next(char c) {
        return links[c - 'a'];
    }
};

class Trie {
private:
    Node* root;
public:
    Trie() {
        root = new Node();
    }

    void insert(std::string& word) {
        Node* n = root;

        for (char c: word) {
            if (!n->contains(c)) {
                n->put(c, new Node());
            }

            n = n->next(c);
        }
    }

    bool stars_with(std::string& prefix) {
        Node* n = root;

        for (char c : prefix) {
            if (!n->contains(c)) {
                return false;
            }

            n = n->next(c);
        }

        return true;
    }
};

class Solution {
private:
    int by_trie(vector<string>& words) {
        int n = words.size();
        int cnt = 0;

        for (int i = 0; i < n; ++i) {
            Trie prefix;
            Trie suffix;

            prefix.insert(words[i]);
            std::string rev = words[i];
            std::reverse(rev.begin(), rev.end());
            suffix.insert(rev);

            for (int j = 0; j < i; ++j) {
                if (words[j].size() > words[i].size()) {
                    continue;
                }

                std::string pre = words[j];
                std::string rev_word = pre;
                std::reverse(rev_word.begin(), rev_word.end());

                if (prefix.stars_with(pre) && suffix.stars_with(rev_word)) {
                    ++cnt;
                }
            }
        }

        return cnt;
    }
public:
    int countPrefixSuffixPairs(vector<string>& words) {
        return by_trie(words);
    }
};