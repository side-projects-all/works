/*
You are given an array of binary strings strs and two integers m and n.

Return the size of the largest subset of strs such that there are at most m 0's and n 1's in the subset.

A set x is a subset of a set y if all elements of x are also elements of y.

 

Example 1:

Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
Output: 4
Explanation: The largest subset with at most 5 0's and 3 1's is {"10", "0001", "1", "0"}, so the answer is 4.
Other valid but smaller subsets include {"0001", "1"} and {"10", "1", "0"}.
{"111001"} is an invalid subset because it contains 4 1's, greater than the maximum of 3.

Example 2:

Input: strs = ["10","0","1"], m = 1, n = 1
Output: 2
Explanation: The largest subset is {"0", "1"}, so the answer is 2.

 

Constraints:

    1 <= strs.length <= 600
    1 <= strs[i].length <= 100
    strs[i] consists only of digits '0' and '1'.
    1 <= m, n <= 100


*/

class Solution {
private:
    std::vector<int> zerosOnes(std::string& s) {
        //v[0]: counts of zeros; v[1]: counts of ones
        std::vector<int> v(2, 0);
        for (char c : s) {
            ++v[c - '0'];
        }

        return v;
    }
    int iterative(std::vector<std::string>& strs, int m, int n) {
        std::vector<std::vector<int>> mem(m + 1, std::vector<int>(n + 1, 0));

        for (std::string& s : strs) {
            std::vector<int> counts = zerosOnes(s);

            for (int zeros = m; zeros >= counts[0]; --zeros) {
                for (int ones = n; ones >= counts[1]; --ones) {
                    mem[zeros][ones] = std::max(1 + mem[zeros - counts[0]][ones - counts[1]], mem[zeros][ones]);
                }
            }
        }

        return mem[m][n];
    }

    int recursive(std::vector<std::string>& strs, int m, int n, int i, 
                                                            std::vector<std::vector<std::vector<int>>>& mem) {
        if (i == strs.size()) {
            return 0;
        }

        if (mem[i][m][n] != -1) {
            return mem[i][m][n];
        }

        std::vector<int> counts = zerosOnes(strs[i]);
        int use = 0;
        int notUse = 0;

        if (m - counts[0] >= 0 && n - counts[1] >= 0) {
            use = 1 + recursive(strs, m - counts[0], n - counts[1], i + 1, mem);
        }

        notUse = recursive(strs, m, n, i + 1, mem);

        mem[i][m][n] = std::max(use, notUse);

        return mem[i][m][n];
    }
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        /*
        std::vector<std::vector<std::vector<int>>> mem(strs.size(), 
                                                        std::vector<std::vector<int>>(m + 1, 
                                                                                std::vector<int>(n + 1, -1)));
        */
        //return recursive(strs, m, n, 0, mem);

        return iterative(strs, m, n);
    }
};