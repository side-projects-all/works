/*
Given a string s, partition s such that every
substring
of the partition is a
palindrome
. Return all possible palindrome partitioning of s.

 

Example 1:

Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Example 2:

Input: s = "a"
Output: [["a"]]

 

Constraints:

    1 <= s.length <= 16
    s contains only lowercase English letters.


*/

class Solution {
private:
    std::vector<std::vector<std::string>> recursive(std::string& s) {
        int N = s.size();
        std::vector<std::vector<int>> mem(N + 1, std::vector<int>(N + 1, 0));

        for (int i = 0; i < N + 1; ++i) {
            mem[i][i] = 1;
        }

        std::vector<std::vector<std::string>> ans;
        std::vector<std::string> curr;

        std::function<void(int)> bt = [&](int begin) {
            if (begin >= N) {
                ans.push_back(curr);
                return;
            }

            for (int end = begin; end < N; ++end) {
                

                if (s[begin] == s[end] && (end - begin <= 2 || mem[begin + 1][end - 1])) {
                    mem[begin][end] = 1;
                    curr.push_back(s.substr(begin, end - begin + 1));
                    bt(end + 1);
                    curr.pop_back();
                }
            }
        };

        bt(0);

        return ans;
    }

    bool isPalindrome(int b, int e, const std::string& s) {

        while (b < e) {
            if (s[b] != s[e]) {
                return false;
            }

            ++b;
            --e;
        }

        return true;
    }

    std::vector<std::vector<std::string>> backtracking(std::string& s) {
        int N = s.size();

        std::vector<std::vector<std::string>> ans;
        std::vector<std::string> curr;

        std::function<void(int)> bt = [&](int begin) {
            if (begin >= N) {
                ans.push_back(curr);
                return;
            }

            for (int end = begin; end < N; ++end) {
                curr.push_back(s.substr(begin, end - begin + 1));

                if (isPalindrome(begin, end, s)) {
                    bt(end + 1);
                }

                curr.pop_back();
            }
        };

        bt(0);

        return ans;
    }
public:
    vector<vector<string>> partition(string s) {
        //corner case
        if (s.size() == 1) {
            return std::vector<std::vector<std::string>>{{s}};
        }

        //return backtracking(s);
        return recursive(s);
    }
};