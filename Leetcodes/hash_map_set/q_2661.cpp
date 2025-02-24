/*
You are given a 0-indexed integer array arr, and an m x n integer matrix mat. arr and mat both contain all the integers in the range [1, m * n].

Go through each index i in arr starting from index 0 and paint the cell in mat containing the integer arr[i].

Return the smallest index i at which either a row or a column will be completely painted in mat.

 

Example 1:
image explanation for example 1

Input: arr = [1,3,4,2], mat = [[1,4],[2,3]]
Output: 2
Explanation: The moves are shown in order, and both the first row and second column of the matrix become fully painted at arr[2].

Example 2:
image explanation for example 2

Input: arr = [2,8,7,4,1,3,5,6,9], mat = [[3,2,5],[1,4,6],[8,7,9]]
Output: 3
Explanation: The second column becomes fully painted at arr[3].

 

Constraints:

    m == mat.length
    n = mat[i].length
    arr.length == m * n
    1 <= m, n <= 10^5
    1 <= m * n <= 10^5
    1 <= arr[i], mat[r][c] <= m * n
    All the integers of arr are unique.
    All the integers of mat are unique.


*/

class Solution {
public:
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        int rows = mat.size();
        int cols = mat[0].size();

        std::vector<int> cols_cnt(cols, rows);
        std::vector<int> rows_cnt(rows, cols);
        std::vector<std::pair<int, int>> val_to_index(rows * cols + 1); 

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                val_to_index[mat[r][c]] = {r, c};
            }
        }

        for (int i = 0; i < arr.size(); ++i) {
            auto p = val_to_index[arr[i]];
            --rows_cnt[p.first];
            --cols_cnt[p.second];

            if (rows_cnt[p.first] == 0 || cols_cnt[p.second] == 0) {
                return i;
            }
        }

        return -1;
    }
};