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
        int cnt = 1;
        int layers = (n + 1) / 2;
        for (int lr = 0; lr < layers; ++lr) {

            //top left to right
            for (int ptr = lr; ptr < n - lr; ++ptr) {
                ans[lr][ptr] = cnt++;
            }

            //top right to bottom right
            for (int ptr = lr + 1; ptr < n - lr; ++ptr) {
                ans[ptr][n - lr - 1] = cnt++;
            }

            //bottom right to bottom left
            for (int ptr = n - lr - 2; ptr >= lr; --ptr) {
                ans[n - lr - 1][ptr] = cnt++;
            }

            //bottom left to top left
            for (int ptr = n - lr - 2; ptr > lr; --ptr) {
                ans[ptr][lr] = cnt++;
            }
        }

        return ans;
    }
};