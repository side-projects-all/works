/*
Given two strings s and t, return the number of distinct subsequences of s which equals t.

The test cases are generated so that the answer fits on a 32-bit signed integer.

 

Example 1:

Input: s = "rabbbit", t = "rabbit"
Output: 3
Explanation:
As shown below, there are 3 ways you can generate "rabbit" from s.
rabbbit
rabbbit
rabbbit

Example 2:

Input: s = "babgbag", t = "bag"
Output: 5
Explanation:
As shown below, there are 5 ways you can generate "bag" from s.
babgbag
babgbag
babgbag
babgbag
babgbag

 

Constraints:

    1 <= s.length, t.length <= 1000
    s and t consist of English letters.


*/

struct pair_hash {
    template<class T1, class T2>
    size_t operator() (const std::pair<T1, T2>& p) const {
        //basically, we use integer here, so auto means int
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        return h1 ^ h2;
    }
};

class Solution {
private:
    int recursive(std::string& s, std::string& t, int i, int j, 
                    std::unordered_map<std::pair<int, int>, int, pair_hash>& mem) {
        
        int S = s.size();
        int T = t.size();

        if (i == S || j == T || (S - i < T - j)) {
            return j == T ? 1 : 0;
        }

        std::pair<int, int> key = std::make_pair(i, j);

        if (mem.find(key) != mem.end()) {
            return mem[key];
        }

        int ans = recursive(s, t, i + 1, j, mem);

        if (s[i] == t[j]) {
            ans += recursive(s, t, i + 1, j + 1, mem);
        }

        mem[key] = ans;

        return ans;
    }
public:
    int numDistinct(string s, string t) {
        std::unordered_map<std::pair<int, int>, int, pair_hash> mem;

        return recursive(s, t, 0, 0, mem);
    }
};