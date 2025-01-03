/*
Given an m x n matrix matrix and an integer k, return the max sum of a rectangle in the matrix such that its sum is no larger than k.

It is guaranteed that there will be a rectangle with a sum no larger than k.

 

Example 1:

Input: matrix = [[1,0,1],[0,-2,3]], k = 2
Output: 2
Explanation: Because the sum of the blue rectangle [[0, 1], [-2, 3]] is 2, and 2 is the max number no larger than k (k = 2).

Example 2:

Input: matrix = [[2,2,-1]], k = 3
Output: 3

 

Constraints:

    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 100
    -100 <= matrix[i][j] <= 100
    -10^5 <= k <= 10^5

 

Follow up: What if the number of rows is much larger than the number of columns?

*/

class Solution {
private:
    int max_by_kadane(std::vector<int>& row_sum) {
        int max_ans = INT_MIN;
        int curr = 0;
        for (int& n : row_sum) {
            curr = std::max(curr + n, n);
            max_ans = std::max(max_ans, curr);
        }

        return max_ans;
    }
    void update_row_sum(std::vector<int>& row_sum, int k, int& ans) {
        int kadane_sum = max_by_kadane(row_sum);

        if (kadane_sum <= k) {
            ans = std::max(ans, kadane_sum);
            return;
        }

        int sum = 0;
        std::set<int> sorted_sum;
        std::set<int>::iterator it;

        sorted_sum.insert(0);
        for (int& n : row_sum) {
            sum += n;   //sum is a prefix!!
            it = sorted_sum.lower_bound(sum - k);

            if (it != sorted_sum.end()) {
                ans = std::max(ans, sum - *it);
            }

            sorted_sum.insert(sum);
        }
    }

    int by_sorted_set(vector<vector<int>>& matrix, int& k) {
        int ans = INT_MIN;
        int rows = matrix.size();
        int cols = matrix[0].size();

        if (rows >= cols) {
            std::vector<int> row_sum(cols);

            for (int i = 0; i < rows; ++i) {
                std::fill(row_sum.begin(), row_sum.end(), 0);

                for (int r = i; r < rows; ++r) {
                    for (int c = 0; c < cols; ++c) {
                      //this add matrix[r][c] for every column by row! not accumulate col to next col!!
                      row_sum[c] += matrix[r][c];
                    }

                    update_row_sum(row_sum, k, ans);

                    if (ans == k) {
                        return ans;
                    }
                }
            }
        } else {
            std::vector<int> col_sum(rows);

            for (int i = 0; i < cols; ++i) {
                std::fill(col_sum.begin(), col_sum.end(), 0);

                for (int c = i; c < cols; ++c) {
                    for (int r = 0; r < rows; ++r) {
                        col_sum[r] += matrix[r][c];
                    }

                    update_row_sum(col_sum, k, ans);

                    if (ans == k) {
                        return ans;
                    }
                }
            }
        }
        
        return ans;
    }
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        return by_sorted_set(matrix, k);
    }
};