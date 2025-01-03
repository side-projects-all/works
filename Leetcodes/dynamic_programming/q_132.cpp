/*
Given a string s, partition s such that every
substring
of the partition is a
palindrome
.

Return the minimum cuts needed for a palindrome partitioning of s.

 

Example 1:

Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.

Example 2:

Input: s = "a"
Output: 0

Example 3:

Input: s = "ab"
Output: 1

 

Constraints:

    1 <= s.length <= 2000
    s consists of lowercase English letters only.


*/

class Solution {
private:
    int from_palindrome_center(std::string& s) {
        int n = s.size();
        std::vector<int> cuts_mem(n);
        for (int i = 1; i < n; ++i) {
            cuts_mem[i] = i;
        }

        std::function<void(int, int)> find_min_cuts = [&cuts_mem, &s, &n](int b, int e) {
            for (int begin = b, end = e; begin >= 0 && end < n && s[begin] == s[end]; 
                --begin, ++end) {

                int new_cut = (begin == 0) ? 0 : cuts_mem[begin - 1] + 1;
                cuts_mem[end] = std::min(cuts_mem[end], new_cut);
            }
        };

        for (int mid = 0; mid < n; ++mid) {
            find_min_cuts(mid, mid);
            find_min_cuts(mid - 1, mid);
        }

        return cuts_mem[n - 1];
    }
    int iterative_optimize(std::string& s) {
        int n = s.size();
        std::vector<int> mem_pCut(n);
        std::vector<std::vector<bool>> mem_isP(n, std::vector<bool>(n));

        for (int e = 0; e < n; ++e) {
            int min_cut = e;

            for (int b = 0; b <= e; ++b) {
                if (s[b] == s[e] && (e - b <= 2 || mem_isP[b + 1][e - 1])) {
                    mem_isP[b][e] = true;
                    //b - 1 means previous one's end!
                    min_cut = (b == 0) ? 0 : std::min(min_cut, mem_pCut[b - 1] + 1);
                }
            }

            mem_pCut[e] = min_cut;
        }

        return mem_pCut[n - 1];
    }
    int iterative(std::string& s) {
        int n = s.size();
        std::vector<int> mem_pCut(n);
        std::vector<std::vector<bool>> mem_isP(n, std::vector<bool>(n));

        //build palindrome memo 2d array
        for (int e = 0; e < n; ++e) {
            for (int b = 0; b <= e; ++b) {
                if (s[b] == s[e] && (e - b <= 2 || mem_isP[b + 1][e - 1])) {
                    mem_isP[b][e] = true;
                }
            }
        }

        for (int e = 0; e < n; ++e) {
            int min_cut = e;

            for (int b = 0; b <= e; ++b) {
                if (mem_isP[b][e]) {

                    //b - 1 means previous one's end!
                    min_cut = (b == 0) ? 0 : std::min(min_cut, mem_pCut[b - 1] + 1);
                }
            }

            mem_pCut[e] = min_cut;
        }

        return mem_pCut[n - 1];
    }

    std::vector<int> mem_pCut;
    std::vector<std::vector<int>> mem_isP;
    bool isPalindrome(std::string& s, int b, int e) {
        if (mem_isP[b][e] == 0) {
            return false;
        }

        if (mem_isP[b][e] == 1) {
            return true;
        }

        int b1 = b;
        int e1 = e;
        while (b1 < e1) {
            if (s[b1] != s[e1]) {

                mem_isP[b1][e1] = 0;
                while (b1 != b && e1 != e) {
                    --b1;
                    ++e1;
                    mem_isP[b1][e1] = 0;
                }
                break;
            }

            mem_isP[b1][e1] = 1;
            ++b1;
            --e1;
        }

        return mem_isP[b][e];
    }

    int recursive(std::string& s, int b, int e, int min_cut) {
        if (b == e || isPalindrome(s, b, e)) {
            return 0;
        }

        if (mem_pCut[b] != -1) {
            return mem_pCut[b];
        }

        for (int end_now = b; end_now <= e; ++end_now) {
            if (isPalindrome(s, b, end_now)) {
                min_cut = std::min(min_cut, 1 + recursive(s, end_now + 1, e, min_cut));
            }
        }

        return mem_pCut[b] = min_cut;
    }
public:
    int minCut(string s) {
        //mem_pCut.resize(s.size(), -1);
        //mem_isP.resize(s.size(), std::vector<int>(s.size(), -1));

        //return recursive(s, 0, s.size() - 1, s.size() - 1);
        //return iterative(s);
        
        //return iterative_optimize(s);
        return from_palindrome_center(s);
    }
};