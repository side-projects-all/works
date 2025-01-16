/*
You are given an array of strings words and a string pref.

Return the number of strings in words that contain pref as a prefix.

A prefix of a string s is any leading contiguous substring of s.

 

Example 1:

Input: words = ["pay","attention","practice","attend"], pref = "at"
Output: 2
Explanation: The 2 strings that contain "at" as a prefix are: "attention" and "attend".

Example 2:

Input: words = ["leetcode","win","loops","success"], pref = "code"
Output: 0
Explanation: There are no strings that contain "code" as a prefix.

 

Constraints:

    1 <= words.length <= 100
    1 <= words[i].length, pref.length <= 100
    words[i] and pref consist of lowercase English letters.


*/

struct Node {
    Node* next[26]{ nullptr };
    int cnt = 0;
};

class Trie {
private:
    Node* root;
public:
    Trie() : root{ new Node() } {

    }

    void add(std::string& w) {
        Node* curr = root;

        for (char c : w) {
            if (curr->next[c - 'a'] == nullptr) {
                curr->next[c - 'a'] = new Node();
            }

            curr = curr->next[c - 'a'];
            ++curr->cnt;
        }
    }

    int cnt(std::string& w) {
        Node* curr = root;

        for (char c : w) {
            if (curr->next[c - 'a'] == nullptr) {
                return 0;
            }

            curr = curr->next[c - 'a'];
        }

        return curr->cnt;
    }
};
class Solution {
private:
    int by_trie(vector<string>& words, string& pref) {
        Trie trie;

        for (std::string& w : words) {
            trie.add(w);
        }

        return trie.cnt(pref);
    }

    int naive(vector<string>& words, string& pref) {
        int cnt = 0;

        for (std::string& w : words) {

            int i = 0;
            for (; i < pref.size(); ++i) {
                if (w[i] != pref[i]) {
                    break;
                }
            }

            if (i == pref.size()) {
                ++cnt;
            }
        }

        return cnt;
    }

public:
    int prefixCount(vector<string>& words, string pref) {
        //return naive(words, pref);
        return by_trie(words, pref);
    }
};