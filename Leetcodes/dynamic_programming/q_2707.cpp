/*
You are given a 0-indexed string s and a dictionary of words dictionary. You have to break s into one or more non-overlapping substrings such that each substring is present in dictionary. There may be some extra characters in s which are not present in any of the substrings.

Return the minimum number of extra characters left over if you break up s optimally.

 

Example 1:

Input: s = "leetscode", dictionary = ["leet","code","leetcode"]
Output: 1
Explanation: We can break s in two substrings: "leet" from index 0 to 3 and "code" from index 5 to 8. There is only 1 unused character (at index 4), so we return 1.

Example 2:

Input: s = "sayhelloworld", dictionary = ["hello","world"]
Output: 3
Explanation: We can break s in two substrings: "hello" from index 3 to 7 and "world" from index 8 to 12. The characters at indices 0, 1, 2 are not used in any substring and thus are considered as extra characters. Hence, we return 3.

 

Constraints:

    1 <= s.length <= 50
    1 <= dictionary.length <= 50
    1 <= dictionary[i].length <= 50
    dictionary[i] and s consists of only lowercase English letters
    dictionary contains distinct words


*/

class Solution {
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        //std::unordered_set<std::string> dic(dictionary.begin(), dictionary.end());
        //std::unordered_map<int, int> m;
        //return recursive(s, 0, dic, m);
        //return iterative_with_set(s, dictionary);
        return iterative_with_trie(s, dictionary);
    }

private:
    struct Node {
        bool is_end = false;
        Node* children[26] = {nullptr};
    };

    Node* root;

    int iterative_with_trie(std::string& s, std::vector<std::string>& dictionary) {

        create_trie(dictionary);
        std::vector<int> dp(s.size() + 1);

        for (int b = s.size() - 1; b >= 0; --b) {
            dp[b] = dp[b + 1] + 1;
            Node* n = root;

            for (int e = b; e < s.size(); ++e) {

                if (n->children[s[e] - 'a'] == nullptr) {
                    break;
                }

                n = n->children[s[e] - 'a'];
                if (n->is_end) {
                    dp[b] = std::min(dp[b], dp[e + 1]);
                }
            }
        }

        return dp[0];
    }

    void create_trie(std::vector<std::string>& dictionary) {
        root = new Node();

        for (const auto& s : dictionary) {
            Node* n = root;

            for (char c : s) {

                if (n->children[c - 'a'] == nullptr) {
                    n->children[c - 'a'] = new Node();
                }

                n = n->children[c - 'a'];
            }

            n->is_end = true;
        } 
    }

    int iterative_with_set(std::string& s, std::vector<std::string>& dictionary) {
        std::unordered_set<std::string> dic(dictionary.begin(), dictionary.end());
        std::vector<int> dp(s.size() + 1);  //at index i, its min skipped characters

        for (int b = s.size() - 1; b >= 0; --b) {
            dp[b] = dp[b + 1] + 1;

            for (int e = b; e < s.size(); ++e) {

                if (dic.find(s.substr(b, e - b + 1)) != dic.end()) {
                    dp[b] = std::min(dp[b], dp[e + 1]);
                }
            }
        }

        return dp[0];
    }

    int recursive(string& s, int begin, std::unordered_set<std::string>& dic, std::unordered_map<int, int>& m) {

        if (begin == s.size()) {
            return 0;
        }

        if (m.find(begin) != m.end()) {
            return m[begin];
        }

        int ans = recursive(s, begin + 1, dic, m) + 1;  //skip this character

        //not skip
        for (int end = begin; end < s.size(); ++end) {
            
            if (dic.find(s.substr(begin, end - begin + 1)) != dic.end()) {
                ans = std::min(ans, recursive(s, end + 1, dic, m));
            }
        }

        return m[begin] = ans;
    }
};