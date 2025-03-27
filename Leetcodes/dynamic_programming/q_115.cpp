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
/*
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
*/

class Solution {
private:
    int by_iterative_dp(string& s, string& t) {
        int sn = s.size();
        int tn = t.size();
        if (sn == tn) {
            return s == t;
        }

        if (sn < tn) {
            return 0;
        }

        std::vector<std::vector<unsigned int>> dp(sn + 1, std::vector<unsigned int>(tn + 1));
        for (int i = 0; i <= sn; ++i) {
            dp[i][0] = 1;
        }

        for (int i = 1; i <= sn; ++i) {
            for (int j = 1; j <= tn; ++j) {
                dp[i][j] += dp[i - 1][j];           //not choose

                if (s[i - 1] == t[j - 1]) {         //choose
                    dp[i][j] += dp[i - 1][j - 1];
                }
            }
        }

        return dp[sn][tn];
    }
    int recursive(string& s, string& t, std::vector<std::vector<int>>& mem, int i, int j) {
        if ((i == s.size() && j < t.size()) || (s.size() - i < t.size() - j)) {
            return 0;
        }
        
        if (j == t.size()) {
            return 1;
        }

        if (mem[i][j] != -1) {
            return mem[i][j];
        }

        mem[i][j] = recursive(s, t, mem, i + 1, j);

        if (s[i] == t[j]) {
            mem[i][j] += recursive(s, t, mem, i + 1, j + 1);
        }

        return mem[i][j];
    }
    int by_recursive_dp(string& s, string& t) {
        int ls = s.size();
        int lt = t.size();
        std::vector<std::vector<int>> mem(ls + 1, std::vector<int>(lt + 1, -1));

        return recursive(s, t, mem, 0, 0);
    }
public:
    int numDistinct(string s, string t) {
        if (s.size() < t.size()) {
            return 0;
        }

        if (s.size() == t.size()) {
            return s == t;
        }

        //return by_recursive_dp(s, t);
        return by_iterative_dp(s, t);
    }
};