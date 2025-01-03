/*
Given a rectangular pizza represented as a rows x cols matrix containing the following characters: 'A' (an apple) and '.' (empty cell) and given the integer k. You have to cut the pizza into k pieces using k-1 cuts. 

For each cut you choose the direction: vertical or horizontal, then you choose a cut position at the cell boundary and cut the pizza into two pieces. If you cut the pizza vertically, give the left part of the pizza to a person. If you cut the pizza horizontally, give the upper part of the pizza to a person. Give the last piece of pizza to the last person.

Return the number of ways of cutting the pizza such that each piece contains at least one apple. Since the answer can be a huge number, return this modulo 10^9 + 7.

 

Example 1:

Input: pizza = ["A..","AAA","..."], k = 3
Output: 3 
Explanation: The figure above shows the three ways to cut the pizza. Note that pieces must contain at least one apple.

Example 2:

Input: pizza = ["A..","AA.","..."], k = 3
Output: 1

Example 3:

Input: pizza = ["A..","A..","..."], k = 1
Output: 1

 

Constraints:

    1 <= rows, cols <= 50
    rows == pizza.length
    cols == pizza[i].length
    1 <= k <= 10
    pizza consists of characters 'A' and '.' only.


*/

class Solution {
private:
    int recursive(vector<string>& pizza, int k) {
        int rows = pizza.size();
        int cols = pizza[0].size();

        std::vector<std::vector<int>> apples(rows + 1, std::vector<int>(cols + 1));
        std::vector<std::vector<std::vector<int>>> mem(k, std::vector<std::vector<int>>(rows, 
                                                                            std::vector<int>(cols, -1)));

        //because every cut will left the right or bottom part of pizza, we do prefix sum for that cell!!
        for (int r = rows - 1; r >= 0; --r) {
            for (int c = cols - 1; c >= 0; --c) {
                apples[r][c] = (pizza[r][c] == 'A') + apples[r + 1][c] + 
                                    apples[r][c + 1] - apples[r + 1][c + 1];

                mem[0][r][c] = apples[r][c] > 0;
            }
        }

        const int MOD = 1000000007;
        std::function<int(int, int, int)> recur = [&](int remains, int r, int c) -> int {
            if (apples[r][c] == 0) {
                return 0;
            }

            if (remains == 0) {
                return 1;
            }

            if (mem[remains][r][c] != -1) {
                return mem[remains][r][c];
            }

            int ans = 0;
            for (int next_r = r + 1; next_r < rows; ++next_r) {
                if (apples[r][c] - apples[next_r][c] > 0) {
                    ans = (ans + recur(remains - 1, next_r, c)) % MOD;
                }
            }

            for (int next_c = c + 1; next_c < cols; ++next_c) {
                if (apples[r][c] - apples[r][next_c] > 0) {
                    ans = (ans + recur(remains - 1, r, next_c)) % MOD;
                }
            }

            return mem[remains][r][c] = ans;
        };

        return recur(k - 1, 0, 0);
    }
    int iterative(vector<string>& pizza, int k) {
        int rows = pizza.size();
        int cols = pizza[0].size();

        std::vector<std::vector<int>> apples(rows + 1, std::vector<int>(cols + 1));
        std::vector<std::vector<std::vector<int>>> mem(k, std::vector<std::vector<int>>(rows, 
                                                                            std::vector<int>(cols)));

        for (int r = rows - 1; r >= 0; --r) {
            for (int c = cols - 1; c >= 0; --c) {
                apples[r][c] = (pizza[r][c] == 'A') + apples[r + 1][c] + 
                                    apples[r][c + 1] - apples[r + 1][c + 1];

                mem[0][r][c] = apples[r][c] > 0;
            }
        }

        const int MOD = 1000000007;
        for (int remain = 1; remain < k; ++remain) {
            for (int r = 0; r < rows; ++r)  {
                for (int c = 0; c < cols; ++c) {
                    for (int next_r = r + 1; next_r < rows; ++next_r) {
                        if (apples[r][c] - apples[next_r][c] > 0) {
                            (mem[remain][r][c] += mem[remain - 1][next_r][c]) %= MOD;
                        }
                    }

                    for (int next_c = c + 1; next_c < cols; ++next_c) {
                        if (apples[r][c] - apples[r][next_c] > 0) {
                            (mem[remain][r][c] += mem[remain - 1][r][next_c]) %= MOD;
                        }
                    }
                }
            }
        }

        return mem[k - 1][0][0];
    }
public:
    int ways(vector<string>& pizza, int k) {
        //return iterative(pizza, k);
        return recursive(pizza, k);
    }
};