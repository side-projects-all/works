/*
There is a new alien language that uses the English alphabet. However, the order of the letters is unknown to you.

You are given a list of strings words from the alien language's dictionary. Now it is claimed that the strings in words are
sorted lexicographically
by the rules of this new language.

If this claim is incorrect, and the given arrangement of string in words cannot correspond to any order of letters, return "".

Otherwise, return a string of the unique letters in the new alien language sorted in lexicographically increasing order by the new language's rules. If there are multiple solutions, return any of them.

 

Example 1:

Input: words = ["wrt","wrf","er","ett","rftt"]
Output: "wertf"

Example 2:

Input: words = ["z","x"]
Output: "zx"

Example 3:

Input: words = ["z","x","z"]
Output: ""
Explanation: The order is invalid, so return "".

 

Constraints:

    1 <= words.length <= 100
    1 <= words[i].length <= 100
    words[i] consists of only lowercase English letters.


*/

class Solution {
private:
    std::string by_topological_sort(vector<string>& words) {
        std::unordered_map<char, std::vector<char>> adj;
        std::unordered_map<char, int> indegree;
        int n = words.size();

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < words[i].size(); ++j) {
                indegree[words[i][j]] = 0;
            }
        }

        for (int i = 0; i < n - 1; ++i) {

            std::string w1 = words[i];
            std::string w2 = words[i + 1];

            if (w1.size() > w2.size() && w1.find(w2) == 0) {
                return "";
            }

            int sz = std::min(w1.size(), w2.size());
            for (int j = 0; j < sz; ++j) {

                if (w1[j] != w2[j]) {
                    adj[w1[j]].push_back(w2[j]);
                    ++indegree[w2[j]];
                    break;
                }
            }
        }
        
        std::queue<char> q;
        for (auto& p : indegree) {
            if (p.second == 0) {
                q.push(p.first);
            }
        }

        std::string ans;
        while (!q.empty()) {
            char c = q.front();
            q.pop();

            ans += c;

            for (const char next : adj[c]) {
                --indegree[next];

                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        return ans.size() == indegree.size() ? ans : "";
    }
public:
    string alienOrder(vector<string>& words) {
        return by_topological_sort(words);
    }
};
