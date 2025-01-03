/*
You are given a string s, and an array of pairs of indices in the string pairs where pairs[i] = [a, b] indicates 2 indices(0-indexed) of the string.

You can swap the characters at any pair of indices in the given pairs any number of times.

Return the lexicographically smallest string that s can be changed to after using the swaps.

 

Example 1:

Input: s = "dcab", pairs = [[0,3],[1,2]]
Output: "bacd"
Explaination: 
Swap s[0] and s[3], s = "bcad"
Swap s[1] and s[2], s = "bacd"

Example 2:

Input: s = "dcab", pairs = [[0,3],[1,2],[0,2]]
Output: "abcd"
Explaination: 
Swap s[0] and s[3], s = "bcad"
Swap s[0] and s[2], s = "acbd"
Swap s[1] and s[2], s = "abcd"

Example 3:

Input: s = "cba", pairs = [[0,1],[1,2]]
Output: "abc"
Explaination: 
Swap s[0] and s[1], s = "bca"
Swap s[1] and s[2], s = "bac"
Swap s[0] and s[1], s = "abc"

 

Constraints:

    1 <= s.length <= 10^5
    0 <= pairs.length <= 10^5
    0 <= pairs[i][0], pairs[i][1] < s.length
    s only contains lower case English letters.


*/

class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        len = s.size();
        root = std::vector<int>(len);
        rank = std::vector<int>(len, 1);
        for (int j = 0; j < len; ++j) {
            root[j] = j;
        }

        int n1 = 0;
        int n2 = 0;
        for (int i = 0; i < pairs.size(); ++i) {
            n1 = pairs[i][0];
            n2 = pairs[i][1];
            unionSet(n1, n2);
        }

        std::unordered_map<int, std::vector<int>> rootToComp;
        int r = 0;
        for (int k = 0; k < len; ++k) {
            r = find(k);
            rootToComp[r].push_back(k);
        }

        std::string str(len, ' ');
        std::vector<int> list;
        
        for (auto m : rootToComp) {
            list = m.second;

            std::vector<char> chars;
            for (int index : list) {
                chars.push_back(s[index]);
            }

            std::sort(chars.begin(), chars.end());

            for (int n = 0; n < list.size(); ++n) {
                str[list[n]] = chars[n];
            }
        }

        return str;
    }
private:
    std::vector<int> root;
    std::vector<int> rank;
    int len;

    int find(int i) {
        
        if (root[i] == i) {
            return i;
        }
    
        int root_i = i;
        
        while (root[root_i] != root_i) {
            root_i = root[root_i];
        }

        int old_root = -1;
        while (i != root_i) {
            old_root = root[i];
            root[i] = root_i;
            i = old_root;
        }

        return root_i;
    }

    void unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            
            if (rank[rootX] > rank[rootY]) {
                root[rootY] = rootX;
                find(y);
            } else if (rank[rootX] < rank[rootY]) {
                root[rootX] = rootY;
                find(x);
            } else {
                root[rootY] = rootX;
                rank[rootX] += 1;
                    
            }
        }
    }
};