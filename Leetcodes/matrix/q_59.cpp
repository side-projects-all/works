/*
Given a positive integer n, generate an n x n matrix filled with elements from 1 to n2 in spiral order.

 

Example 1:

Input: n = 3
Output: [[1,2,3],[8,9,4],[7,6,5]]

Example 2:

Input: n = 1
Output: [[1]]

 

Constraints:

    1 <= n <= 20


*/

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        std::vector<std::vector<int>> ans(n, std::vector<int>(n));
        int i = 0;
        int lb = 0;
        int rb = n - 1;
        int top = 0;
        int btm = n - 1;

        while (i < n * n) {
            //left to right
            for (int c = lb; c <= rb; ++c, ++i) {
                ans[top][c] = i + 1;
            }

            //top to bottom
            for (int r = top + 1; r <= btm; ++r, ++i) {
                ans[r][rb] = i + 1;
            }

            if (i == n * n) return ans;

            for (int c = rb - 1; c >= lb; --c, ++i) {
                ans[btm][c] = i + 1;
            }

            for (int r = btm - 1; r > top; --r, ++i) {
                ans[r][lb] = i + 1;
            }

            ++lb;
            --rb;
            ++top;
            --btm;
        }


        return ans;
    }
};