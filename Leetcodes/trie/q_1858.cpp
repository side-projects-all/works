/*
Given an array of strings words, find the longest string in words such that every prefix of it is also in words.

    For example, let words = ["a", "app", "ap"]. The string "app" has prefixes "ap" and "a", all of which are in words.

Return the string described above. If there is more than one string with the same length, return the lexicographically smallest one, and if no string exists, return "".

 

Example 1:

Input: words = ["k","ki","kir","kira", "kiran"]
Output: "kiran"
Explanation: "kiran" has prefixes "kira", "kir", "ki", and "k", and all of them appear in words.

Example 2:

Input: words = ["a", "banana", "app", "appl", "ap", "apply", "apple"]
Output: "apple"
Explanation: Both "apple" and "apply" have all their prefixes in words.
However, "apple" is lexicographically smaller, so we return that.

Example 3:

Input: words = ["abc", "bc", "ab", "qwe"]
Output: ""

 

Constraints:

    1 <= words.length <= 10^5
    1 <= words[i].length <= 10^5
    1 <= sum(words[i].length) <= 10^5
    words[i] consists only of lowercase English letters.


*/

class Solution {
public:
    string longestWord(vector<string>& words) {
        //return by_set(words);
        return by_trie(words);
    }
private:
    std::string by_set(vector<string>& words) {
        std::sort(words.begin(), words.end());
        std::unordered_set<std::string> prefixes;
        std::string ans;

        for (auto& w : words) {

            std::string sub = w.substr(0, w.size() - 1);
            if (w.size() == 1 || prefixes.find(sub) != prefixes.end()) {
                prefixes.insert(w);

                if (w.size() > ans.size()) {
                    ans = w;
                }
            }
        }

        return ans;
    }

    std::string by_trie(vector<string>& words) {

        create_trie(words);
        std::string ans;
        for (const auto& w : words) {
            if (has_all_prefixes(w)) {

                if (w.size() > ans.size() || (w.size() == ans.size() && w < ans)) {
                    ans = w;
                }
            }
        }
        return ans;
    }

    struct Node {
        bool is_end = false;
        Node* children[26] = { nullptr };
    };

    Node* root;
    void create_trie(vector<string>& words) {
        root = new Node();

        for (const auto& w : words) {
            Node* node = root;
            
            for (char c : w) {
                int i = c - 'a';

                if (node->children[i] == nullptr) {
                    node->children[i] = new Node();
                }

                node = node->children[i];
            }

            node->is_end = true;
        }
    }

    bool has_all_prefixes(const string& w) {
        Node* node = root;
        for (char c : w) {
            node = node->children[c - 'a'];

            if (node == nullptr || !node->is_end) {
                return false;
            }
        }

        return true;
    }
};