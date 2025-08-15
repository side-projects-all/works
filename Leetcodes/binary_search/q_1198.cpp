/*
Given an m x n matrix mat where every row is sorted in strictly increasing order, return the smallest common element in all rows.

If there is no common element, return -1.

 

Example 1:

Input: mat = [[1,2,3,4,5],[2,4,5,8,10],[3,5,7,9,11],[1,3,5,7,9]]
Output: 5

Example 2:

Input: mat = [[1,2,3],[2,3,4],[2,3,5]]
Output: 2

 

Constraints:

    m == mat.length
    n == mat[i].length
    1 <= m, n <= 500
    1 <= mat[i][j] <= 10^4
    mat[i] is sorted in strictly increasing order.


*/

class Solution {
public:
    int smallestCommonElement(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        for (int i = 0; i < n; ++i) {

            int target = mat[0][i];
            bool find = true;
            for (int r = 1; r < m; ++r) {
                int i = std::lower_bound(mat[r].begin(), mat[r].end(), target) - mat[r].begin();

                if (i < 0 || i >= m || mat[r][i] != target) {
                    find = false;
                    break;
                }
            }

            if (find) return target;
        }

        return -1;
    }
};