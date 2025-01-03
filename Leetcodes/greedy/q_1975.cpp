/*
You are given an n x n integer matrix. You can do the following operation any number of times:

    Choose any two adjacent elements of matrix and multiply each of them by -1.

Two elements are considered adjacent if and only if they share a border.

Your goal is to maximize the summation of the matrix's elements. Return the maximum sum of the matrix's elements using the operation mentioned above.

 

Example 1:

Input: matrix = [[1,-1],[-1,1]]
Output: 4
Explanation: We can follow the following steps to reach sum equals 4:
- Multiply the 2 elements in the first row by -1.
- Multiply the 2 elements in the first column by -1.

Example 2:

Input: matrix = [[1,2,3],[-1,-2,-3],[1,2,3]]
Output: 16
Explanation: We can follow the following step to reach sum equals 16:
- Multiply the 2 last elements in the second row by -1.

 

Constraints:

    n == matrix.length == matrix[i].length
    2 <= n <= 250
    -10^5 <= matrix[i][j] <= 10^5


*/

class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        long long total = 0;
        int min_abs_neg = INT_MAX;
        int neg_cnt = 0;

        for (auto& r : matrix) {
            for (int v : r) {
                total += std::abs(v);
                if (v < 0) {
                    ++neg_cnt;
                }
                min_abs_neg = std::min(min_abs_neg, std::abs(v));
            }
        }

        //deduct if the count of negative numbers is odd
        if (neg_cnt % 2 != 0) {
            total -= 2 * min_abs_neg;
        }

        return total;
    }
};