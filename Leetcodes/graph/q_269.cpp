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
    std::string byTopologicalSort(vector<string>& words) {
        std::unordered_map<char, std::vector<char>> nodeNeighbors;
        std::unordered_map<char, int> indegree;

        
        //build basic structure to store data
        for (const std::string &word : words) {
            for (char c : word) {
                indegree.insert(std::make_pair(c, 0));
                nodeNeighbors.insert(std::make_pair(c, std::vector<char>()));
            }
        }
        

        //find all edges
        for (int i = 0; i < words.size() - 1; ++i) {
            std::string w1 = words[i];
            std::string w2 = words[i + 1];

            //check prefix, check if find from beginning
            if ((w1.size() > w2.size()) && (w1.find(w2) == 0)) {
                return "";
            }

            //find the first not match and insert the corresponding relation, 
            //rest letters did not affect the order, so we just break the inner loop
            int len = std::min(w1.size(), w2.size());
            for (int j = 0; j < len; ++j) {
                if (w1[j] != w2[j]) {
                    //std::vector<char> neighbors = nodeNeighbors[w1[j]];
                    //neighbors.push_back(w2[j]);
                    //nodeNeighbors[w1[j]] = neighbors;
                    nodeNeighbors[w1[j]].push_back(w2[j]);
                    
                    //int count = indegree[w2[j]] + 1;
                    //indegree[w2[j]] = count;
                    
                    ++indegree[w2[j]];

                    break;
                }
            }
        }

        //bfs like topological sort, queue indegree 0 first
        std::string result = "";
        std::queue<char> q;
        for (const auto& [c, ind] : indegree) {
            if (ind == 0) {
                q.push(c);
            }
        }
        //loop queue
        while (!q.empty()) {
            char c = q.front();
            q.pop();
            result += c;

            for (const char next : nodeNeighbors[c]) {
                int count = indegree[next] - 1;
                indegree[next] = count;

                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        return result.size() < indegree.size() ? "" : result;
    }
public:
    string alienOrder(vector<string>& words) {
        return byTopologicalSort(words);
    }
};
